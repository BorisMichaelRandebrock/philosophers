/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:03:14 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/15 18:25:32 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *single_philo_wrapper(void *arg)
// {
//     single_philo(arg);
//     return NULL;
// }


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




int	handle_thread_error(int status)
{
	if (status == 0)
		return (0);
	if (status == EAGAIN)
		print_error("Not enough resources... 😓");
	else if (status == EPERM)
		print_error("inapropiate permissions... 👾");
	else if (status == EINVAL && status == CREATE)
		print_error("The specifies value is invalid... 😬");
	else if (status == EINVAL && (status == JOIN || status == DETACH))
		print_error("The thread is not joinable... 😰");
	else if (status == ESRCH)
		print_error("No thread could be found... 👻");
	else
		print_error("Error: Wrong status for threading... 😓");
	return (1);
}


// static void	*_philo_loop(t_philo *philo)
// {
// 	//cilo de vida

// 	return(philo);
// }

int	threading(pthread_t *thread, void *(*foo)(void *),
	void *data, t_opcode operation)
{
	if (operation == CREATE)
	{
		if (pthread_create(thread, NULL, foo, data) != 0)
			return (handle_thread_error(CREATE));
	}
	else if (operation == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			return (mutex_error_check(JOIN));
	}
	else if (operation == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			return (mutex_error_check(DETACH));
	}
	else
		printf("Check operation code used in threading.\n");
	return (0);
}


/* void	threading(pthread_t *thread, void *(*foo)(void *),
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
} */