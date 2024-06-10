/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:59:59 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/30 10:46:50 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(type_mtx *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(type_mtx *mutex, bool *value)
{
	bool	return_value;

	mutex_handle(mutex, LOCK);
	return_value = *value;
	mutex_handle(mutex, UNLOCK);
	return (return_value);
}

void	set_long(type_mtx *mutex, long *dest, long value)
{
	if (mutex)
		mutex_handle(mutex, LOCK);
	*dest = value;
	if (mutex)
		mutex_handle(mutex, UNLOCK);
}

long	get_long(type_mtx *mutex, long *value)
{
	long	return_value;

	mutex_handle(mutex, LOCK);
	return_value = *value;
	mutex_handle(mutex, UNLOCK);
	return (return_value);
}

long	gettime(void)
{
	struct timeval	time_val;
	long			current_time;

	if (gettimeofday(&time_val, NULL) != 0)
	{
		print_error("Error: gettimeofday failed... ⏱");
		return (1337);
	}
	current_time = (time_val.tv_sec * 1000) + (time_val.tv_usec / 1000);
	return (current_time);
}
