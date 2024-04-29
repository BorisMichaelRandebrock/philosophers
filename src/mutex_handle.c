/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:12:25 by boris             #+#    #+#             */
/*   Updated: 2024/04/29 13:54:33 by brandebr         ###   ########.fr       */
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
        print_error("The mutex value is invalid 😓");
    else if (EINVAL == status && opcode == INIT)
        print_error("The value specified by mutex is invalid ... 🥺");
    else if (EDEADLK == status)
        print_error("Deadlock danger... 😱");
    else if (EPERM == status)
        print_error("The current thread does not hold a lock on mutex.");
    else if (status == ENOMEM)
        print_error("Not enough memory to initialize the mutex... 🫥");
    else if (status == EBUSY && opcode == INIT)
        print_error("Mutex is locked...");
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
        print_error("Error: Wrong opcode for mutex_handle.. 😱");
}
