/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:58:30 by boris             #+#    #+#             */
/*   Updated: 2024/04/27 15:40:15 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

static long ft_atol(const char *str)
{
    long res;
    int i;

    res = 0;
    i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
            || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        pri_error("Error: no number can be negative... 🤬");
    if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res);
}

void	error_parsing(t_table *table, char **argv)
{
    (void)table;
    (void)argv;
    table->number_of_philosophers = ft_atol(argv[1]);
    if (table->number_of_philosophers < 2 || table->number_of_philosophers > 
            PHILO_MAX)
        pri_error("Error: Wrong number of philosophers 🤬");
    table->time_to_die = ft_atol(argv[2]) *1e3;
    table->time_to_eat = ft_atol(argv[3]) *1e3;
    table->time_to_sleep = ft_atol(argv[4]) *1e3;
    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 
            || table->time_to_sleep < 6e4)
        pri_error("Error: Wrong time 🤬");
    if (argv[5])
        table->amount_of_meals = ft_atol(argv[5]);
    else
        table->amount_of_meals = -1;
    print_colours("Welcome to our lovely ", GREEN);
    print_colours("\"Chez Jean-Paul Sartre\" 🍽️ ", YELLOW);
    print_colours("!\n\n", GREEN);
    print_colours("We hope that everything will be to your liking.\n", WHITE);
    print_colours("For now I shall leave you in the hands of ", WHITE);
    print_colours("Maximus", BLUE);
    print_colours(", your Maître, he will take care of your every needs.. \n\n", WHITE);
    print_colours("Enjoy your dinner!\n", MAGENTA);
    printf("🍝");
    
}