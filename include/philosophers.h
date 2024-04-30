/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:36:06 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/30 17:16:12 by brandebr         ###   ########.fr       */
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
	int				id;
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

void	print_error(const char *str);
void	print_colours(const char *str, const char *colour);
int		ft_strlen(const char *str);
void	error_parsing(t_table *table, char **argv);
void	dinner_prep(t_table *table);
void	mutex_handle(type_mtx *mutex, t_opcode opcode);
void 	dinner_start(t_table *table);
int		gettime(int time_type);



void threading(
	pthread_t *thread,
	void *(*foo)(void *),
	void *data,
	t_opcode opccode
);


void	toggle_boolean(type_mtx *mutex, bool *dest, bool *value);
void	dinner(void);
bool	get_bool(type_mtx *mutex,  bool *value);
void	wait_threads(t_table *table);
void	increase_long(type_mtx *mutex, long *value);
void	set_long(type_mtx *mutex, long *dest, long value);
long	get_long(type_mtx *mutex, long *value);
void	set_bool(type_mtx *mutex, bool *dest, bool value);

void	single_philo(void *arg);
void	print_status(t_philosophers_state state, t_philo *philo);
void	reporter(t_philosophers_state state, t_philo *philo);
void	wait_dinner(void *data);




void	restaurant_closing(t_table *table);


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
