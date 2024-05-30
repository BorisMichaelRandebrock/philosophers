/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/30 10:46:50 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	even_odd(t_philo *philo)
{
	if (philo->table->number_of_philosophers % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(200);
	}
	else
	{
		if (philo->id % 2)
			philo_thinks(philo, true);
	}
}
/* void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->threads_created))
		;
} */

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
// void	precise_usleep(long usec, t_table *table)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = gettime();
// 	while (gettime() - start < usec)
// 	{
// 		if (dinner_finished(table))
// 			break ;
// 		elapsed = gettime() - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e4)
// 			usleep(rem / 2);
// 		else
// 			while (gettime() - start < usec)
// 				;
// 	}
// }
void	precise_usleep(long time)
{
/* 	time = gettime(0);
	while (gettime(0) <= time) */
	time = gettime();
	while (gettime() <= time)
		usleep(100);
}
