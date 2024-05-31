/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_starting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/31 17:15:21 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

// static void	lonely_dinner(t_philo *philo)
// {
// 	t_table	*table;
// 	long	start;

// 	table = philo->table;
// 	printf("Pilosopher %ld: ", philo->id);
// 	print_colours("..., am I the only one?..\n", YELLOW);
// 	start = gettime();
// 	printf("Pilo ID NUMBER CHECK %ld\n", philo->id);
// 	mutex_handle(&table->table_mutex, UNLOCK);
// 	 printf("fguyfdsjkldfd");
// 	mutex_handle(&philo->philo_mutex, INIT);
// 	mutex_handle(&philo->right_fork->fork, INIT);
// 	reporter(TAKE_LEFT_FORK, philo);
// 	//usleep(philo->table->time_to_die);
// 	precise_usleep(philo->table->time_to_die / 10000);
// 	// precise_usleep(philo->table->time_to_die / 10000, philo->table);
// 	//precise_usleep(philo->table->time_to_die, philo->table);
// 	reporter(DEAD, philo);
// 	philo_dies(philo);
// 	mutex_handle(&philo->philo_mutex, DESTROY);
// 	funeral(philo->table);
// 	return ;
//}

static void lonely_dinner(t_philo *philo)
{

	print_colours("Pilosopher 1: ", WHITE);
	print_colours("..., am I the only one?..\n", YELLOW);
	// mutex_handle(&philo->left_fork->fork, LOCK);
	// mutex_handle(&philo->right_fork->fork, LOCK);
	reporter(TAKE_LEFT_FORK, philo);
	//usleep(philo->table->time_to_die);
	precise_usleep(philo->table->time_to_die);
	//precise_usleep(philo->table->time_to_die);
	// mutex_handle(&philo->left_fork->fork, UNLOCK);
}


// static void	dinner_party(t_philo *philo)
// {
// 	mutex_handle(&philo->left_fork->fork, INIT);
// 	reporter(TAKE_LEFT_FORK, philo);
// 	mutex_handle(&philo->right_fork->fork, INIT);
// 	reporter(TAKE_RIGHT_FORK, philo);
// 	reporter(EATING, philo);
// 	set_long(&philo->philo_mutex, &philo->last_meal, (philo->last_meal + 1));
// 	if (philo->last_meal == philo->table->amount_of_meals)
// 	{
// 		set_bool(&philo->philo_mutex, &philo->full, true);
// 		mutex_handle(&philo->philo_mutex, DESTROY);
// 	}
// 	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
// 	usleep(philo->table->time_to_eat);
// 	mutex_handle(&philo->left_fork->fork, DESTROY);
// 	mutex_handle(&philo->right_fork->fork, DESTROY);
// 	reporter(SLEEPING, philo);
// 	usleep(philo->table->time_to_sleep);
// 	reporter(THINKING, philo);
// }
static void left_fork(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	if (philo->table->end_dinner == true)
	{
		mutex_handle(&philo->left_fork->fork, UNLOCK);
		return ;
	}
	reporter(TAKE_LEFT_FORK, philo);
}

static void	right_fork(t_philo	*philo)
{
	mutex_handle(&philo->right_fork->fork, LOCK);
	if (philo->table->end_dinner == true)
	{
		mutex_handle(&philo->right_fork->fork, UNLOCK);
		mutex_handle(&philo->left_fork->fork, UNLOCK);
		return ;
	}
	reporter(TAKE_RIGHT_FORK, philo);
	reporter(EATING, philo);
	philo->meals++;
}

static void	dinner_party(t_philo *philo)
{
	if (philo->meals == philo->table->amount_of_meals)
	{
		mutex_handle(&philo->table->table_mutex, LOCK);
		set_bool(&philo->philo_mutex, &philo->full, true);
	//	philo->table->philos_full++;
		set_long(&philo->table->full_mtx, &philo->table->philos_full,
			philo->table->philos_full + 1);
		mutex_handle(&philo->table->table_mutex, UNLOCK);
		return ;
	}
	left_fork(philo);
	right_fork(philo);
	usleep(philo->table->time_to_eat);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	if (philo->table->end_dinner == true)
			return ;
	reporter(SLEEPING, philo);
	usleep(philo->table->time_to_sleep);
	reporter(THINKING, philo);
}

bool	end(t_table *table)
{
	bool	temp;
	mutex_handle(&table->finish_mtx, LOCK);
	temp = table->end_dinner;
	mutex_handle(&table->finish_mtx, UNLOCK);
	return (temp);
}

void	*dinner_rules(void *filo)
{
	t_philo	*philo;
	philo = (t_philo *)filo;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat / 1000);
		//precise_usleep(philo->table->time_to_eat / 1000);
	// while (!philo->table->end_dinner)
	while (!get_bool(&philo->table->full_mtx, &philo->table->end_dinner))
	{
		if (philo->table->number_of_philosophers == 1)
		{
			lonely_dinner(philo);
			break ;
		}
		else
			dinner_party(philo);
	}
	return (NULL);
}

void	*dinner_start(void *m_table)
{
	int		i;
	t_table	*table;
	t_philo *philo;

	table = (t_table *)m_table;
	i = -1;
	table->philos_full = 0;
	//table->start_dinner = gettime();
	//table->end_dinner = false;

	while (++i < table->number_of_philosophers)
	{
		philo = table->philos + i;
		threading(&philo[i].thread_id, &dinner_rules, &philo[i], CREATE);
	/* 	if (threading(&philo[i].thread_id, &dinner_rules, &philo[i],
				CREATE))
			break ;//	return (1); */
	}
	return (NULL);
}


// void	*dinner(void *arg)
// {
// 	t_philo	*philo;
// 	t_table	*table;

// 	philo = (t_philo *)arg;
// 	table = philo->table;
// 	wait_threads(philo->table);
// 	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
//increase_long(&philo->table->table_mutex, &philo->table->numb_threads_runing);
// 	even_odd(philo);
// 	while (!dinner_finished(philo->table))
// 	{
//	// if (table->number_of_philosophers == table->philos_full) //TODOO  sigue
// 		// 	restaurant_closing(philo->table);
// 		if (get_bool(&philo->philo_mutex, &philo->full) || table->philos_full
// 		 	== table->number_of_philosophers)
// 		{
// 			//printf("philo 55555555 %ld full\n", table->philos_full);
// 			restaurant_closing(philo->table);
// 		}
// 		philo_eats(philo);
// 		reporter(SLEEPING, philo);
// 		usleep(philo->table->time_to_sleep);
// //		precise_usleep(philo->table->time_to_sleep, philo->table);
// 		philo_thinks(philo, false);
// 	}
// 	return (NULL);
// }
