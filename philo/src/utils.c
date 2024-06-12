/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/31 18:41:44 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_long(t_mtx *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}

int	left_fork(t_philo *philo)
{
	if (get_bool(&philo->table->finish_mtx, &philo->table->end_dinner))
		return (1);
	mutex_handle(&philo->left_fork->fork, LOCK);
	reporter(TAKE_LEFT_FORK, philo);
	return (0);
}

int	right_fork(t_philo	*philo)
{
	if (get_bool(&philo->table->finish_mtx, &philo->table->end_dinner))
	{
		mutex_handle(&philo->left_fork->fork, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->right_fork->fork, LOCK);
	reporter(TAKE_RIGHT_FORK, philo);
	reporter(EATING, philo);
	set_long(&philo->philo_mutex, &philo->meals, philo->meals + 1);
	return (0);
}
