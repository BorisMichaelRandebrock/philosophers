/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_starting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/09 16:54:11 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

static void	lonely_dinner(t_philo *philo)
{
	printf("Pilosopher %ld: ", philo->id);
	print_colours("..., am I the only one?..\n", YELLOW);
	long	start;

	start	= gettime();
	mutex_handle(&philo->philo_mutex, INIT);
	//wait_threads(philo->table);
	reporter(TAKE_LEFT_FORK, philo);
	//sleep(philo->table->time_to_die / 100000);
	precise_usleep(philo->table->time_to_die / 1000, philo->table);
	reporter(DEAD, philo);
	philo_dies(philo);
	mutex_handle(&philo->philo_mutex, DESTROY);
	restaurant_closing(philo->table);
	return ;
}

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
	increase_long(&philo->table->table_mutex, &philo->table->numb_threads_runing);
	reporter(TAKE_LEFT_FORK, philo);
	while (!dinner_finished(philo->table))
		usleep(200);
		//precise_usleep(200, philo->table);
	return (NULL);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
	increase_long(&philo->table->table_mutex, &philo->table->numb_threads_runing);
	even_odd(philo);
	while (!dinner_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		philo_eats(philo);
		reporter(SLEEPING, philo);
		usleep(philo->table->time_to_sleep);
//		precise_usleep(philo->table->time_to_sleep, philo->table);
		philo_thinks(philo, false);
	}
	return (NULL);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime();
	while (gettime() - start < usec)
	{
		if (dinner_finished(table))
			break ;
		elapsed = gettime() - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (gettime() - start < usec)
				;
	}
}

void	dinner_start(t_table *table)
{
	int		i;

	i = -1;
	table->start_dinner = gettime();
	if (table->number_of_philosophers == 1)
		lonely_dinner(&table->philos[0]);
	else
	{
		while (++i < table->number_of_philosophers)
					threading(&table->philos[i].thread_id, dinner, &table->philos[i], CREATE);
	}
	threading(&table->waiter, (void *(*)(void *))wait_dinner, table, CREATE);
	// printf("--------here i am: %p\n",(void *(*)(void *))wait_dinner);
	set_bool(&table->table_mutex, &table->threads_created, true);
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		threading(&table->philos[i].thread_id, NULL, NULL, JOIN);
	}
	set_bool(&table->table_mutex, &table->end_dinner, true);
	threading(&table->waiter, NULL, NULL, JOIN);
}

// void dinner_start(t_table *table)
// {
// 	int		i;

// 	i = - 1;
// 	table->start_dinner = gettime();
// 	if (table->number_of_philosophers == 1)
// 			lonely_dinner(&table->philos[0]);
// 	else
// 	{

// 		while (++i < table->number_of_philosophers)
// 		{
// 			threading(&table->philos->thread_id, dinner, &table->philos[i], CREATE);
// 			 printf("philo %d\n", i);
// 		}
// 	}
// 	wait_threads(table);
// 	//threading(table->waiter, wait_dinner, table, CREATE);
// 	threading(table->waiter, (void *(*)(void *))wait_dinner, table, CREATE);
// 	table->start_dinner = gettime();
// 	set_bool(table->table_mutex, &table->threads_created, true);
// 	i = -1;
// 	while (++i < table->number_of_philosophers)
// 		threading(&table->philos[i].thread_id, NULL, NULL, JOIN);
// 	set_bool(table->table_mutex, &table->end_dinner, true);
// 	threading(table->waiter, NULL, NULL, JOIN);
// }

