/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_starting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/30 18:22:11 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

void	set_bool(type_mtx *mutex, bool *dest, bool *value)
{
	mutex_handle(&mutex, LOCK);
	*dest = *value;
	mutex_handle(&mutex, UNLOCK);
}

void	dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->threads_runing);
	even_odd(philo);
	while (!dinner_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;

		// reporter(TAKE_LEFT_FORK, philo);
		// reporter(TAKE_RIGHT_FORK, philo);
		// reporter(EATING, philo);
		// reporter(SLEEPING, philo);
		// reporter(THINKING, philo);
	}
	return (NULL);
}




bool  dinner_finished(t_table *table)
{
	if (table->end_dinner == true)
		return (true);
	return (false);
}
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(table))
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
void	single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->threads_runing);
	reporter(TAKE_LEFT_FORK, philo);
	while (!dinner_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

void dinner_start(t_table *table)
{
	int		i;

	i = - 1;
	if (table->number_of_philosophers == 1)
		threading(&table->philos[0].philo_mutex, single_philo,
		&table->philos[0], CREATE);
	else
	{
		while (++i < table->number_of_philosophers)
			threading(&table->philos[i].id, dinner, &table->philos[i], CREATE);
	}
	threading(&table->waiter, wait_dinner, table, CREATE);
	table->start_dinner = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, table->threads_created, true);
	i = -1;
	while (++i < table->number_of_philosophers)
		threading(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, table->end_dinner, true);
	threading(&table->waiter, NULL, NULL, JOIN);
}

