/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:00:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/27 15:31:05 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"



int	main(int argc, char **argv)
{
	(void)argv;
	if (argc >= 5 && argc <= 6)
	{
		t_table table;
		
		error_parsing(&table, argv);
		// print_colours("Hello, Philosopher!\n", GREEN);
		// print_colours("Hello, World!\n", MAGENTA);
	}
	else
		pri_error("Error: Wrong number of arguments 🤬");
	return (0);
}
