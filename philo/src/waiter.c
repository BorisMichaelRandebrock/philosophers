/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:15:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/31 19:26:46 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

void	philo_thinks(t_philo *philo, bool initial)
{
	long	eat;
	long	sleeps;
	long	think;

	if (initial)
		reporter(THINKING, philo);
	/* if (philo->table->number_of_philosophers % 2 == 0)
		return ; */
	eat = philo->table->time_to_eat;
	sleeps = philo->table->time_to_sleep;
	think = (eat * 2) - sleeps;
	if (think < 0)
		think = 0;
	usleep(think/* * 42*/);
}

bool	philo_dies(t_philo *philo)
{
	long	elapsed;
	long 	time_to_die;

	elapsed = (gettime() - get_long(&philo->philo_mutex, &philo->last_meal));
	time_to_die = philo->table->time_to_die / 1000;
	if (time_to_die <= elapsed)
	{
	//	philo->death = true;
		set_bool(&philo->table->dead_filo_mutex, &philo->table->dead, true);
		reporter(DEAD, philo);
		//set_bool(&philo->table->finish_mtx, &philo->table->end_dinner, true);
		return (1);
	}
	return(0);
}
/*
void	waiter(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (table->number_of_philosophers == table->philos_full)
		{
			set_bool(&table->table_mutex, &table->end_dinner, true);
			restaurant_closing(table);
		}
		else if (philo_dies(&table->philos[i]))
		{
			//reporter(DEAD, &table->philos[i]);
			funeral(table);
		}
		i++;
		if (table->number_of_philosophers == i)
			i = 0;
	}
} */
void	waiter(t_table *table)
{
	while (!get_bool(&table->finish_mtx, &table->end_dinner))
	{

		if (table->number_of_philosophers == table->philos_full)
		{
			set_bool(&table->finish_mtx, &table->end_dinner, true);
			restaurant_closing(table);
		}
		else if (get_bool(&table->dead_filo_mutex, &table->dead))
		{
			//i = -1;
			//  while (++i < table->number_of_philosophers)
			// 	mutex_handle(&table->forks[i].fork, UNLOCK);
			//reporter(DEAD, &table->philos[i]);
			set_bool(&table->finish_mtx, &table->end_dinner, true);
			funeral(table);
		}
	}
}
