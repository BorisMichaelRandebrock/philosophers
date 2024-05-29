/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_ending.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:42:32 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/28 19:10:30 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

void	restaurant_closing(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->number_of_philosophers)
		threading(&table->philos[i++].thread_id, NULL, NULL, JOIN);
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philo = &table->philos[i];
		mutex_handle(&table->forks[i].fork, DESTROY);
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&table->table_mutex, DESTROY);
	mutex_handle(&table->print_mutex, DESTROY);
	mutex_handle(&table->full_mtx, DESTROY);
	mutex_handle(&table->finish_mtx, DESTROY);
	print_colours("We hope you have enjoied the soirée, and shall\n"
		 "		be delighted to be seeing you again very soon...\n", GREEN);
		 printf("😃\n");
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	exit(0);
}
static void	final_speech()
{
	print_colours("We are deeply saddened by the loss of our valued guest.\n"
		"    Our thoughts are with their loved ones during this difficult time.\n"
		"	  We are here to offer any support and assistance we can.\n", MAGENTA);
		 printf("		✞\n");
}

void	funeral(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	final_speech();
	while (i < table->number_of_philosophers)
		threading(&table->philos[i++].thread_id, NULL, NULL, JOIN);
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philo = &table->philos[i];
		mutex_handle(&table->forks[i].fork, DESTROY);
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&table->table_mutex, DESTROY);
	mutex_handle(&table->print_mutex, DESTROY);
	mutex_handle(&table->full_mtx, DESTROY);
	mutex_handle(&table->finish_mtx, DESTROY);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	exit(0);
}
