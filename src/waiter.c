/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:15:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/30 16:16:46 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool all_threads_created(type_mtx *mutex, long *threads,
							long number_of_philosophers)
{
	mutex_handle(&mutex, LOCK);
	if (*threads == number_of_philosophers)
		return (true);
	return (false);
}
static bool	philo_dies(t_philo *philo)
{
	long	time;
	long 	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	long current_time = gettime(MILLISECONDS);
	long last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal);
	time = current_time - last_meal_time;
	time_to_die = philo->table->time_to_die / 1e3;
	if (time > time_to_die)
		return (true);
	return (false);
}

void	set_bool(type_mtx *mutex, bool *dest, bool value)
{
	mutex_handle(&mutex, LOCK);
	*dest = value;
	mutex_handle(&mutex, UNLOCK);
}

void	waitig_dinner(void *data)
{
	int		i;
	t_table *table;

	while (!all_threads_created(&table->table_mutex, table->threads_runing,
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
