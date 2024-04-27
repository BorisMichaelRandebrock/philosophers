/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:12:25 by boris             #+#    #+#             */
/*   Updated: 2024/04/27 17:40:49 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"
#include <errno.h>

static void    mutex_error_check(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK))
        pri_error("The mutex value is invalid 😓");
    else if (EINVAL == status && opcode == INIT)
        pri_error("The value specified by mutex is invalid ... 🥺");
    else if (EDEADLK == status)
        pri_error("Deadlock danger... 😱");
    else if (EPERM == status)
        pri_error("The current thread does not hold a lock on mutex.");
    else if (status == ENOMEM)
        pri_error("Not enough memory to initialize the mutex... 🫥");
    else if (status == EBUSY && opcode == INIT)
        pri_error("Mutex is locked...");
}

void	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
    if (opcode == INIT)
        mutex_error_check(pthread_mutex_init(mutex, NULL), opcode);
    else if (opcode == LOCK)
        mutex_error_check(pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        mutex_error_check(pthread_mutex_unlock(mutex), opcode);
    else if (opcode == DESTROY)
        mutex_error_check(pthread_mutex_destroy(mutex), opcode);
    else
        pri_error("Error: Wrong opcode for mutex_handle.. 😱");
}