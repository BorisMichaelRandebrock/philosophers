/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:15:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/27 19:00:04 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	long	elapsed;
	long 	time_to_die;

	elapsed = (gettime(philo->table->start_dinner)
		- get_long(&philo->philo_mutex,	&philo->last_meal));
	time_to_die = philo->table->time_to_die;
	if (time_to_die >= elapsed)
	{
		set_long(&philo->table->finish_mtx, &philo->table->end_dinner, 1);
		return (1);
	}
	return(0);
	/* if (get_bool(&philo->philo_mutex, &philo->full))
		return (false); */
	/* long current_time = gettime();
	long last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal);
	time = current_time - last_meal_time;
	time_to_die = philo->table->time_to_die / 1000;
	if (time > time_to_die)
	{
		reporter(DEAD, philo);
		set_bool(&philo->philo_mutex, &philo->id, true);
		return (true);
	}
	return (false); */
}
void	philo_eats(t_philo *philo)
{
	if (philo->table->amount_of_meals >= 0
		&& philo->meals == philo->table->amount_of_meals)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
		philo->table->philos_full++;
			//philo->table->philos_full++;//?? TODO sigue
			//printf("amount of full philos: %ld\n", philo->table->philos_full);
			//philo_thinks(philo, true);
	}
	mutex_handle(&philo->left_fork->fork, LOCK);
	reporter(TAKE_LEFT_FORK, philo);
	mutex_handle(&philo->right_fork->fork, LOCK);
	reporter(TAKE_RIGHT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
	philo->meals++;
	reporter(EATING, philo);
	usleep(philo->table->time_to_eat/1000);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

bool	dinner_finished(t_table *table)
{
	if (table->end_dinner == 1)
		return (1);
	return (0);
}

void	waiter(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (philo_dies(&table->philos[i]))
			funeral(table);
		if (table->amount_of_meals == table->philos_full)
			restaurant_closing(table);
		i++;
		if (table->number_of_philosophers == i)
			i = 0;

		/* if (philo_dies(table->philos + i))
		{
			set_bool(&table->table_mutex, &table->end_dinner, true);
			reporter(DEAD, table->philos + i);
			funeral(table);
		}
		else if (table->amount_of_meals > 0
			&& table->philos_full == table->number_of_philosophers)
		{
			set_bool(&table->table_mutex, &table->end_dinner, true);
			restaurant_closing(table);
		}
		i++; */
	}
}
