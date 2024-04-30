// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   dinner_starting.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
// /*   Updated: 2024/04/30 16:04:18 by brandebr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philosophers.h"
// #include "colours.h"

// void	toggle_boolean(type_mtx *mutex, bool *dest, bool *value)
// {
// 	mutex_handle(&mutex, LOCK);
// 	*dest = *value;
// 	mutex_handle(&mutex, UNLOCK);
// }

// void	dinner(void)
// {}
// bool	get_bool(type_mtx *mutex,  bool *value)
// {
// 	bool	return_value;

// 	mutex_handle(&mutex, LOCK);
// 	return_value = *value;
// 	mutex_handle(&mutex, UNLOCK);
// 	return (return_value);
// }
// void	wait_threads(t_table *table)
// {
// 	while (!get_bool(&table->table_mutex, table->threads_created))
// 		;
// }

// void increase_long(type_mtx *mutex, long *value)
// {
// 	mutex_handle(&mutex, LOCK);
// 	(*value)++;
// 	mutex_handle(&mutex, UNLOCK);
// }

// void	set_long(type_mtx *mutex, long *dest, long value)
// {
// 	mutex_handle(&mutex, LOCK);
// 	*dest = value;
// 	mutex_handle(&mutex, UNLOCK);
// }

// long	get_long(type_mtx *mutex, long *value)
// {
// 	long	return_value;

// 	mutex_handle(&mutex, LOCK);
// 	return_value = *value;
// 	mutex_handle(&mutex, UNLOCK);
// 	return (return_value);
// }
// bool  dinner_finished(t_table *table)
// {
// 	if (table->end_dinner == true)
// 		return (true);
// 	return (false);
// }
// void	precise_usleep(long usec, t_table *table)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = gettime(MICROSECONDS);
// 	while (gettime(MICROSECONDS) - start < usec)
// 	{
// 		if (simulation_finished(table))
// 			break ;
// 		elapsed = gettime(MICROSECONDS) - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e4)
// 			usleep(rem / 2);
// 		else
// 			while (gettime(MICROSECONDS) - start < usec)
// 				;
// 	}
// }
// void	single_philo(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	wait_threads(philo->table);
// 	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECONDS));
// 	increase_long(&philo->table->table_mutex, &philo->table->threads_runing);
// 	reporter(TAKE_LEFT_FORK, philo);
// 	while (!dinner_finished(philo->table))
// 		precise_usleep(200, philo->table);
// 	return (NULL);
// }

// void dinner_start(t_table *table)
// {
// 	int		i;

// 	i = - 1;
// 	if (table->number_of_philosophers == 1)
// 		threading(&table->philos[0].philo_mutex, single_philo,
// 		&table->philos[0], CREATE);
// 	else
// 	{
// 		while (++i < table->number_of_philosophers)
// 			threading(&table->philos[i].id, dinner, &table->philos[i], CREATE);
// 	}
// 	//threading(&table->waiter, waiter, table, CREATE);
// 	table->start_dinner = gettime(MILLISECONDS);
// 	toggle_boolean(&table->table_mutex, table->threads_created, true);
// 	i = -1;
// 	while (++i < table->number_of_philosophers)
// 		threading(&table->philos[i].thread_id, NULL, NULL, JOIN);
// 	toggle_boolean(&table->table_mutex, table->end_dinner, true);
// 	threading(&table->waiter, NULL, NULL, JOIN);
// }

