/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:00:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/29 18:55:47 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

static void clear_terminal()
{
    printf("\033[2J\033[H");
  //  fflush(stdout);
}

static void conversation(void)
{
		usleep(6000000);
		clear_terminal();
		print_colours("\nSince everybody is seated...\n", WHITE);
		usleep(500000);
		print_colours("	& orders are taken:\n\n", WHITE);
		usleep(500000);
		print_colours("Lets start the Dinner ", GREEN);
		printf("🍝\n");
		usleep(6000000);
}


int	main(int argc, char **argv)
{
	(void)argv;
	if (argc >= 5 && argc <= 6)
	{
		t_table table;

		error_parsing(&table, argv);
		dinner_prep(&table);
		conversation();
		//dinner_start(&table);

		clear_terminal();
		restaurant_closing(&table);
	}
	else
		print_error("Error: Wrong number of arguments 🤬");
	return (0);
}
