/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:36:06 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/25 18:40:29 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
	int id;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_data *data;
} t_philo;

typedef struct s_data
{
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_eat;
	int *forks;
	t_philo *philos;
	pthread_mutex_t *fork_mutex;
	pthread_mutex_t print_mutex;
	pthread_mutex_t dead_mutex;
	struct timeval start;
} t_data;

void	pri_error(const char *str);
void	print_colours(const char *str, const char *colour);
int		ft_strlen(const char *str);
void	init_data(t_data *data, int argc, char **argv);
void	init_philos(t_data *data);
void	*philo_life(void *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_dead(t_philo *philo);
void	philo_take_forks(t_philo *philo);
void	philo_drop_forks(t_philo *philo);
void	philo_print(t_philo *philo, char *str);
int		get_time(struct timeval start);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);

#endif
