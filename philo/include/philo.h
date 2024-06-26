/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:36:06 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/09 18:22:10 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DEAD,
	BREAK
}	t_philosophers_state;

typedef enum e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}	t_time;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	bool		full;
	long		id;
	long		meals;
	long		last_meal;
	pthread_t	thread_id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mtx		philo_mutex;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	bool	dead;
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	amount_of_meals;
	t_mtx	dead_filo_mutex;
	bool	end_dinner;
	long	philos_full;
	long	start_dinner;
	t_fork	*forks;
	t_philo	*philos;
	t_mtx	table_mutex;
	t_mtx	print_mutex;
	t_mtx	full_mtx;
	t_mtx	finish_mtx;
}	t_table;

// ->main.c
void	clear_terminal(void);

// ->error_parsing.c
int		error_parsing(t_table *table, char **argv);

// ->print_utils.c
int		ft_strlen(const char *str);
int		print_error(const char *str);
void	print_colours(const char *str, const char *colour);
void	reporter(t_philosophers_state state, t_philo *philo);

// ->dinner_prep.c
int		init_table(t_table *table);

// ->mutex_handle.c
int		mutex_error_check(int status);
int		mutex_handle(t_mtx *mutex, t_opcode opcode);

// ->dinner_starting.c
void	*dinner_start(void *table);
void	*dinner_rules(void *data);

// ->threading.c
int		threading(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode operation);
int		handle_thread_error(int status);

// ->setters_getters.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
long	gettime(void);

// ->utils.c
void	increase_long(t_mtx *mutex, long *value);
int		left_fork(t_philo *philo);
int		right_fork(t_philo	*philo);

// ->waiter.c
void	philo_thinks(t_philo *philo, bool initial);
bool	philo_dies(t_philo *philo);
void	waiter(t_table *table);

// ->dinner_ending.c
int		restaurant_closing(t_table *table);
int		funeral(t_table *table);

#endif
