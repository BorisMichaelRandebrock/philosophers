/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:03:14 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/23 16:22:48 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* void *single_philo_wrapper(void *arg)
{
    single_philo(arg);
    return NULL;
} */


// void	threading(pthread_t *thread, void *(*foo)(void *),
// 		void *data, t_opcode opccode)
// {
// 	if (opccode == CREATE)
// 	{
// 		if (pthread_create(thread, NULL, foo, data) != 0)
// 			print_error("Error: Could not create thread... 😓");
// 	}
// 	else if (opccode == JOIN)
// 	{
// 		if (pthread_join(*thread, NULL) != 0)
// 			print_error("Error: Could not join thread... 😓");
// 	}
// 	else if (opccode == DETACH)
// 	{
// 		if (pthread_detach(*thread) != 0)
// 			print_error("Error: Could not detach thread... 😓");
// 	}
// 	else
// 		print_error("Error: Wrong opcode for threading... 😓");
// }




static void handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("Not enough resources... 😓");
	else if (status == EPERM)
		print_error("inapropiate permissions... 👾");
	else if (status == EINVAL && opcode == CREATE)
		print_error("The specifies value is invalid... 😬");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		print_error("The thread is not joinable... 😰");
	else if (status == ESRCH)
		print_error("No thread could be found... 👻");
	else
		print_error("Error: Wrong opcode for threading... 😓");
}


// static void	*_philo_loop(t_philo *philo)
// {
// 	//cilo de vida

// 	return(philo);
// }


void	threading(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
//handle_thread_error(pthread_create(thread, _philo_loop, NULL, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		print_error("Error: Wrong opcode for threading... 😓");
}
