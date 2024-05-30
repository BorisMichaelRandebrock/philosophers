/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:00:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/30 10:46:50 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

void clear_terminal()
{
	write(1,"\033[2J\033[H", 8);
   // printf("\033[2J\033[H");
  //  fflush(stdout);
}

static void conversation(void)
{
		/* usleep(6000000);//TODO undo the comments
		clear_terminal(); */
		print_colours("\nSince everybody is seated...\n", WHITE);
		// usleep(800000);
		print_colours("	& orders are taken:\n\n", WHITE);
		// usleep(800000);
		print_colours("Let's start the Dinner ", GREEN);
		printf("🍝\n");
		// usleep(1000000);
}
/*
int	main(int argc, char **argv)
{
	if (argc >= 5 && argc <= 6)
	{
		t_table table;

		clear_terminal();
		error_parsing(&table, argv);
		dinner_prep(&table);
		conversation();
		dinner_start(&table);
		if (dinner_start(&table) !=0)
		{
			restaurant_closing(&table);
			return (1);
		 }
		//mutex_handle(&table.table_mutex, UNLOCK);
		//table.start_dinner = gettime(0);

	}
	else
		print_error("Error: Wrong number of arguments 🤬");
	return (0);
} */

int	main(int argc, char **argv)
{
	t_table	table;
	clear_terminal();
	if (argc < 5 || argc > 6)
		print_error("Error: Wrong number of arguments");
	error_parsing(&table, argv);
	conversation();
	init_table(&table);
	/* if (init_table(&table) != 0)
		restaurant_closing(&table);
 */	//table.start_dinner = gettime();
	waiter(&table);
}
