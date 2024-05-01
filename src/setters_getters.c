/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:59:59 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/01 14:46:00 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void	set_bool(type_mtx *mutex, bool *dest, bool value)
{
	mutex_handle(&mutex, LOCK);
	*dest = value;
	mutex_handle(&mutex, UNLOCK);
}

bool	get_bool(type_mtx *mutex,  bool *value)
{
	bool	return_value;

	mutex_handle(&mutex, LOCK);
	return_value = *value;
	mutex_handle(&mutex, UNLOCK);
	return (return_value);
}

void	set_long(type_mtx *mutex, long *dest, long value)
{
	mutex_handle(&mutex, LOCK);
	*dest = value;
	mutex_handle(&mutex, UNLOCK);
}

long	get_long(type_mtx *mutex, long *value)
{
	long	return_value;

	mutex_handle(&mutex, LOCK);
	return_value = *value;
	mutex_handle(&mutex, UNLOCK);
	return (return_value);
}
int	gettime(int time_type)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		print_error("Error: gettimeofday failed... ⏱");
	if (time_type == MILLISECONDS)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (time_type == MICROSECONDS)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else if (time_type == SECONDS)
		return (time.tv_sec + time.tv_usec / 1e6);
	else
		print_error("Error: Wrong time type... ⏱\n"
			"Please use MILLISECONDS, MICROSECONDS or SECONDS");
	return (1337);
}
