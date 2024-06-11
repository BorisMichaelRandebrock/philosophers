/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:58:30 by boris             #+#    #+#             */
/*   Updated: 2024/06/10 15:03:16 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

static long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		print_error("Error: no number can be negative... 🤬");
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

static int	meal_amounts(t_table *table, char *meals)
{
	table->amount_of_meals = ft_atol(meals);
	if (table->amount_of_meals == 0)
		if (print_error("As nobody wants to eat anything..\n"
			" 				we wish you a very nice evening.\n") ==  1)
			return (1);
	return (0);
}

static	void	welcome(void)
{
	print_colours("\nWelcome to our lovely ", GREEN);
	print_colours("\"Chez Sartre\" 🍽️\n\n", YELLOW);
	print_colours("We hope that everything will be to your liking.\n", WHITE);
	print_colours("For now I shall leave you in the hands of ", WHITE);
	print_colours("Maximus", BLUE);
	print_colours(", your Maître, he will take care of "
		"your every needs.. \n\n", WHITE);
	print_colours("Enjoy your stay!\n", MAGENTA);
}

int	error_parsing(t_table *table, char **argv)
{
	table->number_of_philosophers = ft_atol(argv[1]);
	if (table->number_of_philosophers < 1 || table->number_of_philosophers
		> PHILO_MAX)
		if (print_error("Error: Wrong number of philosophers 🤬\n") == 1)
			return (1);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		if (print_error("Error: Wrong time 🤬\n") == 1)
			return (1);
	if (argv[5])
	{
		if (meal_amounts(table, argv[5]) == 1)
			return (1);
	}
	else
		table->amount_of_meals = -1;
	welcome();
	return (0);
}
