/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:00:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/06/12 17:59:30 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

void	clear_terminal(void)
{
	write(1, "\033[2J\033[H", 8);
}

/*static void	conversation(void)
{
	print_colours("	& orders are taken:\n\n", WHITE);
	print_colours("\nSince everybody is seated...\n", WHITE);
	print_colours("Let's start the Dinner ", GREEN);
	printf("🍝\n");
}*/
static void	conversation(void)
{
	usleep(6000000);
	clear_terminal();
	print_colours("\nSince everybody is seated...\n", WHITE);
	usleep(800000);
	print_colours("	& orders are taken:\n\n", WHITE);
	usleep(800000);
	print_colours("Let's start the Dinner ", GREEN);
	printf("🍝\n");
	usleep(1000000);
}

int	main(int argc, char **argv)
{
	t_table	table;

	clear_terminal();
	if (argc < 5 || argc > 6)
		if (print_error("Error: Wrong number of arguments") != 0)
			return (1);
	if (error_parsing(&table, argv) != 0)
		return (1);
	conversation();
	init_table(&table);
	waiter(&table);
	return (0);
}
