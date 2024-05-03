/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:36:06 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/01 17:56:51 by boris            ###   ########.fr       */
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
#include <unistd.h>
//# include <sys/wait.h>
#include <errno.h>

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
typedef	pthread_mutex_t	type_mtx;


typedef struct 		s_fork
{
	type_mtx		fork;
	int 			fork_id;
}					t_fork;

typedef struct 		s_philo
{
	pthread_t		id;
	bool			full;
	long			meals;
	long			last_meal;
	pthread_t 		thread_id;
	t_fork 			*left_fork;
	t_fork 			*right_fork;
	type_mtx		philo_mutex;
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
	type_mtx		*table_mutex;
	type_mtx 		print_mutex;
}					t_table;







// ->main.c
void 	clear_terminal();

// ->error_parsing.c
void	error_parsing(t_table *table, char **argv);

// ->print_utils.c
int		ft_strlen(const char *str);
void	print_error(const char *str);
void	print_colours(const char *str, const char *colour);
void	reporter(t_philosophers_state state, t_philo *philo);

// ->dinner_prep.c
void	dinner_prep(t_table *table);

// ->mutex_handle.c
void	mutex_handle(type_mtx *mutex, t_opcode opcode);

// ->dinner_starting.c
void	single_philo(void *arg);
void	*dinner(void *arg);
void	precise_usleep(long usec, t_table *table);
void 	dinner_start(t_table *table);

// ->threading.c
void threading(pthread_t *thread, void *(*foo)(void *), void *data,
	t_opcode opccode);
void *single_philo_wrapper(void *arg);
//void threading(pthread_t *thread, void *(*foo)(void *), void *data,

// ->setters_getters.c
void	set_bool(type_mtx *mutex, bool *dest, bool value);
bool	get_bool(type_mtx *mutex,  bool *value);
void	set_long(type_mtx *mutex, long *dest, long value);
long	get_long(type_mtx *mutex, long *value);
int		gettime(int time_type);

// ->sync_utils.c
void	even_odd(t_philo *philo);
void	wait_threads(t_table *table);
void	increase_long(type_mtx *mutex, long *value);


// ->waiter.c
void	philo_thinks(t_philo *philo);
bool	philo_dies(t_philo *philo);
void	philo_eats(t_philo *philo);
bool	dinner_finished(t_table *table);
void	wait_dinner(void *data);

// ->dinner_ending.c
void	restaurant_closing(t_table *table);

#endif
