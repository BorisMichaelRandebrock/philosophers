/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:36:06 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/27 22:17:22 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdint.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

typedef enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DEAD
}				t_philosophers_state;

typedef enum 	e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}				t_time;

typedef enum 		e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}					t_opcode;

typedef struct s_table	t_table;

typedef struct 		s_fork
{
	pthread_mutex_t fork;
	int 			fork_id;
}					t_fork;

typedef struct 		s_philo
{
	int				id;
	bool			full;
	long			meals;
	long			last_meal;
	pthread_t 		thread_id;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}					t_philo;

typedef struct 		s_table
{
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			amount_of_meals;
	long			number_of_philosophers;
	long			start_dinner;
	bool			end_dinner;
	bool			threads_created;
	long			threads_runing;
	pthread_t		*waiter;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t table_mutex;
	pthread_mutex_t print_mutex;
}					t_table;

void	pri_error(const char *str);
void	print_colours(const char *str, const char *colour);
int		ft_strlen(const char *str);
void	error_parsing(t_table *table, char **argv);
void	dinner_prep(t_table *table);
void	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);


//void	init_data(t_data *data, int argc, char **argv);
//void	init_philos(t_data *data);
// void	*philo_life(void *philo);
// void	philo_eat(t_philo *philo);
// void	philo_sleep(t_philo *philo);
// void	philo_think(t_philo *philo);
// void	philo_dead(t_philo *philo);
// void	philo_take_forks(t_philo *philo);
// void	philo_drop_forks(t_philo *philo);
// void	philo_print(t_philo *philo, char *str);
// int		get_time(struct timeval start);

#endif
