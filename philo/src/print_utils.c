/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:00:29 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/29 16:02:48 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_error(const char *str)
{
	printf(RED"%s"RES, str);
	exit(1);
}

void	print_colours(const char *str, const char *colour)
{
	(void)colour;
	(void)str;
	write(1, colour, ft_strlen(colour));
	write(1, str, ft_strlen(str));
	write(1, RES, sizeof(RES));
	//printf("%s%s"RES, colour, str);
}

void	reporter(t_philosophers_state state, t_philo *philo)
{
	long	time;

	time = gettime() - philo->table->start_dinner;
	mutex_handle(&philo->table->print_mutex, LOCK);
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	else
	{
		if ((state == TAKE_LEFT_FORK || state == TAKE_RIGHT_FORK)
			&& !philo->table->end_dinner)
			printf("Time: %-10ld %ld has taken a fork ⋔\n", time, philo->id);
		else if (state == EATING && !philo->table->end_dinner)
			//printf("Time: %-10ld %ld is eating... 🍝\n", time, philo->id);//TODO
			printf("Time: %-10ld %ld is eating... 🍝 %ld\n", time, philo->id,
			(philo->meals +1));//TODO
		else if (state == SLEEPING && !philo->table->end_dinner)
			printf("Time: %-10ld %ld is sleeping... 💤\n", time, philo->id);
		else if (state == THINKING && !philo->table->end_dinner)
			printf("Time: %-10ld %ld is thinking... 💭\n", time, philo->id);
		else if (state == DEAD)
			printf("Time: %-10ld %ld died... 💀\n", time, philo->id);
		else if (state  == BREAK)
			printf("Time: %-10ld %ld we where on a break\n", time, philo->id);
	}
	mutex_handle(&philo->table->print_mutex, UNLOCK);
}
