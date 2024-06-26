/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:59:08 by boris             #+#    #+#             */
/*   Updated: 2024/05/31 19:26:46 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

int	thread_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = table->philos;
	while (++i < table->number_of_philosophers)
	{
		if (threading(&philo[i].thread_id, &dinner_rules,
				&philo[i], CREATE) != 0)
			return (1);
	}
	return (0);
}

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int		philo_nbr;

	philo_nbr = philo->table->number_of_philosophers;
	if (philo->id == 1)
	{
		philo->right_fork = &forks[philo_position];
		philo->left_fork = &forks[philo_nbr - 1];
	}
	else
	{
		philo->right_fork = &forks[philo_position];
		philo->left_fork = &forks[philo_position - 1];
	}
}

static void	philo_init(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->last_meal = table->start_dinner;
		philo->meals = 0;
		philo->full = false;
		mutex_handle(&philo->philo_mutex, INIT);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

static void	create_data_mtx(t_table *table)
{
	mutex_handle(&table->table_mutex, INIT);
	mutex_handle(&table->print_mutex, INIT);
	mutex_handle(&table->full_mtx, INIT);
	mutex_handle(&table->finish_mtx, INIT);
	mutex_handle(&table->dead_filo_mutex, INIT);
}

int	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->philos_full = 0;
	table->end_dinner = 0;
	table->dead = false;
	create_data_mtx(table);
	table->forks = malloc(sizeof(t_fork) * table->number_of_philosophers);
	if (!table->forks)
		print_error("Malloc forks failed.. ");
	while (++i < table->number_of_philosophers)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i + 1;
	}
	table->philos = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!table->philos)
		print_error("Philo Malloc failed..");
	table->start_dinner = gettime();
	philo_init(table);
	if (thread_init(table) == 0)
		return (1);
	return (0);
}
