/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_starting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/07 14:37:22 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

void	single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECONDS));
	increase_long(philo->table->table_mutex, &philo->table->threads_runing);
	reporter(TAKE_LEFT_FORK, philo);
	while (!dinner_finished(philo->table))
		precise_usleep(200, philo->table);
	//return (NULL);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECONDS));
	increase_long(philo->table->table_mutex, &philo->table->threads_runing);
	even_odd(philo);
	while (!dinner_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		philo_eats(philo);
		reporter(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		philo_thinks(philo);

		// reporter(TAKE_LEFT_FORK, philo);
		// reporter(TAKE_RIGHT_FORK, philo);
		// reporter(EATING, philo);
		// reporter(SLEEPING, philo);
		// reporter(THINKING, philo);
	}
	return (NULL);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (dinner_finished(table))
			break ;
		elapsed = gettime(MICROSECONDS) - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (gettime(MICROSECONDS) - start < usec)
				;
	}
}

void dinner_start(t_table *table)
{
	int		i;

	i = - 1;
	if (table->number_of_philosophers == 1)
		//threading(&table->philos[0].id, single_philo, &table->philos[0], CREATE);
		 //threading(&table->philos[0].philo_mutex, single_philo,
		 threading(&table->philos->thread_id, single_philo_wrapper,
		 		&table->philos[0], CREATE);
		// threading(&table->philos[0].id, single_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->number_of_philosophers)
			threading(&table->philos->thread_id, dinner, &table->philos[i], CREATE);
	}
	threading(table->waiter, (void *(*)(void *))wait_dinner, table, CREATE);
	table->start_dinner = gettime(MILLISECONDS);
	set_bool(table->table_mutex, &table->threads_created, true);
	i = -1;
	while (++i < table->number_of_philosophers)
		threading(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(table->table_mutex, &table->end_dinner, true);
	threading(table->waiter, NULL, NULL, JOIN);
}

