/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_starting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/31 19:35:32 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

static void	lonely_dinner(t_philo *philo)
{
	print_colours("Pilosopher 1: ", WHITE);
	print_colours("..., am I the only one?..\n", YELLOW);
	reporter(TAKE_LEFT_FORK, philo);
	usleep(philo->table->time_to_die);
	philo_dies(philo);
}

static void	dinner_party(t_philo *philo)
{
	if (get_long(&philo->philo_mutex, &philo->meals)
		== philo->table->amount_of_meals)
	{
		mutex_handle(&philo->table->full_mtx, LOCK);
		set_bool(&philo->philo_mutex, &philo->full, true);
		set_long(NULL, &philo->table->philos_full,
			philo->table->philos_full + 1);
		mutex_handle(&philo->table->full_mtx, UNLOCK);
		return ;
	}
	if (philo_dies(philo) != 0)
		return ;
	if (left_fork(philo) == 1 || right_fork(philo) == 1)
		return ;
	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
	usleep(philo->table->time_to_eat);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	if (get_bool(&philo->table->finish_mtx, &philo->table->end_dinner))
		return ;
	reporter(SLEEPING, philo);
	usleep(philo->table->time_to_sleep);
	reporter(THINKING, philo);
}

void	*dinner_rules(void *filo)
{
	t_philo	*philo;

	philo = (t_philo *)filo;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat - 10);
	while (!get_bool(&philo->table->finish_mtx, &philo->table->end_dinner)
		&& !get_bool(&philo->philo_mutex, &philo->full))
	{
		if (philo->table->number_of_philosophers == 1)
		{
			lonely_dinner(philo);
			break ;
		}
		else
			dinner_party(philo);
	}
	return (NULL);
}

void	*dinner_start(void *m_table)
{
	int		i;
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)m_table;
	i = -1;
	table->philos_full = 0;
	while (++i < table->number_of_philosophers)
	{
		philo = table->philos + i;
		if (threading(&philo[i].thread_id, &dinner_rules, &philo[i],
				CREATE) != 0)
			break ;
	}
	return (NULL);
}
