/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/09 15:52:49 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	even_odd(t_philo *philo)
{
	if (philo->table->number_of_philosophers % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(200);
		//printf("...");
			//precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			philo_thinks(philo);
	}
}
void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->threads_created))
		;
}

void increase_long(type_mtx *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}

bool all_threads_created(type_mtx *mutex, long *threads,
							long number_of_philosophers)
{
	mutex_handle(mutex, LOCK);
	if (*threads == number_of_philosophers)
		return (true);
	return (false);
}
