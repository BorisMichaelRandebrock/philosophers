/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_ending.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:42:32 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/09 13:38:26 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

void	restaurant_closing(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philo = table->philos + i;
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&table->print_mutex, DESTROY);
	mutex_handle(&table->table_mutex, DESTROY);
	print_colours("We hope you have enjoied the soirée, and shall\n"
		 "		be delighted to be seeing you again very soon...\n", GREEN);
		 printf("😃\n");
	free(table->forks);
	free(table->philos);
	exit(0);
}
