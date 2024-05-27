/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_starting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:37 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/27 19:24:48 by brandebr         ###   ########.fr       */
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

	printf("Pilosopher %ld: ", philo->id);
	print_colours("..., am I the only one?..\n", YELLOW);
	mutex_handle(&philo->right_fork->fork, LOCK);
	reporter(TAKE_LEFT_FORK, philo);
	precise_usleep(philo->table->time_to_die);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
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
static void	dinner_party(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	reporter(TAKE_LEFT_FORK, philo);
	mutex_handle(&philo->right_fork->fork, LOCK);
	reporter(TAKE_RIGHT_FORK, philo);
	reporter(EATING, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, (philo->last_meal + 1));
	if (philo->last_meal == philo->table->amount_of_meals)
	{
		mutex_handle(&philo->table->table_mutex, LOCK);
		set_long(&philo->table->full_mtx, &philo->table->philos_full,
			philo->table->philos_full + 1);
		mutex_handle(&philo->table->table_mutex, UNLOCK);
	}
	set_long(&philo->philo_mutex, &philo->last_meal,
		gettime(&philo->table->start_dinner));
	precise_usleep(philo->table->time_to_eat);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	reporter(SLEEPING, philo);
	precise_usleep(philo->table->time_to_sleep);
	reporter(THINKING, philo);
}

// void	*single_philo(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	wait_threads(philo->table);
// 	set_long(&philo->philo_mutex, &philo->last_meal, gettime());
//increase_long(&philo->table->table_mutex, &philo->table->numb_threads_runing);
// 	reporter(TAKE_LEFT_FORK, philo);
// 	while (!dinner_finished(philo->table))
// 		usleep(200);
// 		//precise_usleep(200, philo->table);
// 	return (NULL);
// }



void	*dinner_rules(void *table)
{
	t_philo	*philo;

	philo = (t_philo *)table;
	// table->start_dinner = gettime();
	mutex_handle(&philo->table->table_mutex, LOCK);
	mutex_handle(&philo->table->table_mutex, UNLOCK);
	/* mutex_handle(&philo->philo_mutex, LOCK);
	mutex_handle(&philo->philo_mutex, UNLOCK); */
	if (philo->table->number_of_philosophers > 1 && philo->id % 2 == 0)
		precise_usleep(philo->table->time_to_eat / 10);
		// precise_usleep(philo->table->time_to_eat / 10, philo->table);
	while (!dinner_finished(philo->table))
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

int	dinner_start(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	table->philos_full = 0;
	table->start_dinner = gettime();
	table->end_dinner = false;
	philo = table->philos;
	while (++i < table->number_of_philosophers)
	{
		if (threading(&philo[i].thread_id, &dinner_rules, &philo[i],
				CREATE) != 0)
			return (1);
	}
	return (0);
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