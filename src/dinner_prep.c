/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:59:08 by boris             #+#    #+#             */
/*   Updated: 2024/04/30 16:46:44 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
    int     philo_nbr;

    philo_nbr = philo->table->number_of_philosophers;
    philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
    philo->right_fork = &forks[philo_position];
    if (philo->id % 2 == 0)
    {
        philo->left_fork = &forks[philo_position];
        philo->right_fork = &forks[(philo_position + 1) % philo_nbr];
    }
}


static void	philo_init(t_table *table)
{
    int     i;
    t_philo *philo;

    i = -1;
    while (++i < table->number_of_philosophers)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals = 0;
        mutex_handle(&philo->philo_mutex, INIT);
        philo->table = table;
        assign_forks(philo, table->forks, i);
    }
    table->threads_created = true;
}

void	dinner_prep(t_table *table)
{
    int     i;

    i = -1;
    table->end_dinner = false;
    table->threads_created = false;
    table->threads_runing = 0;
    table->philos = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!table->philos)
		print_error("Malloc failed...");
    table->forks = malloc(sizeof(t_fork) * table->number_of_philosophers);
	if (!table->forks)
		print_error("Malloc failed...");
    mutex_handle(table->table_mutex, INIT);
  //  mutex_handle(&table->table_mutex, INIT);
    while (++i < table->number_of_philosophers)
    {
        mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}
