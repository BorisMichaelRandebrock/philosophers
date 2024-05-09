/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:15:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/09 16:52:49 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_thinks(t_philo *philo, bool initial)
{
	long	eat;
	long	sleeps;
	long	think;

	if (initial)
		reporter(THINKING, philo);
	if (philo->table->number_of_philosophers % 2 == 0)
		return ;
	eat = philo->table->time_to_eat;
	sleeps = philo->table->time_to_sleep;
	think = (eat * 2) - sleeps;
	if (think < 0)
		think = 0;
	usleep(think/* * 42*/);
	//precise_usleep((think * 42), philo->table);

}

bool	philo_dies(t_philo *philo)
{
	long	time;
	long 	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	long current_time = gettime();
	long last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal);
	time = current_time - last_meal_time;
	time_to_die = philo->table->time_to_die / 1000;
	if (time > time_to_die)
		return (true);
	return (false);
}
void	philo_eats(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	reporter(TAKE_LEFT_FORK, philo);
	mutex_handle(&philo->right_fork->fork, LOCK);
	reporter(TAKE_RIGHT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
	philo->meals++;
	reporter(EATING, philo);
	usleep(philo->table->time_to_eat/1000);
//	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->amount_of_meals > 0
		&& philo->meals >= philo->table->amount_of_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	// set_long(&philo->philo_mutex, &philo->meals, get_long(
			//		&philo->philo_mutex, &philo->meals) + 1);
	// mutex_handle(&philo->philo_mutex, UNLOCK);
}
bool	dinner_finished(t_table *table)
{
	if (table->end_dinner == true)
		return (true);
	return (false);
}

void	*wait_dinner(void *data)
{
	int		i;
	t_table *table;

	table = (t_table *)data;
	while (!all_threads_created(&table->table_mutex, &table->numb_threads_runing,
								table->number_of_philosophers))
			;
	while (!dinner_finished(table))
	{
		i =-1;
		while (++i < table->number_of_philosophers && !table->end_dinner)
		{
			if (philo_dies(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_dinner, true);
				reporter(DEAD, table->philos + i);
			}
		}
	}
	return (NULL);
}
