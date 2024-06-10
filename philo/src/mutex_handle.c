/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:12:25 by boris             #+#    #+#             */
/*   Updated: 2024/05/30 18:47:57 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"
#include <errno.h>

int	mutex_error_check(int status)
{
	if (status == INIT)
		printf("Problem initializing the mutex.\n");
	if (status == LOCK)
		printf("Problem locking the mutex.\n");
	if (status == UNLOCK)
		printf("Problem unlocking the mutex.\n");
	if (status == DESTROY)
		printf("Problem destroying the mutex.\n");
	return (1);
}

int	mutex_handle(type_mtx *mutex, t_opcode opcode)
{
	if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (mutex_error_check(INIT));
	}
	else if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (mutex_error_check(LOCK));
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (mutex_error_check(UNLOCK));
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (mutex_error_check(DESTROY));
	}
	return (0);
}
