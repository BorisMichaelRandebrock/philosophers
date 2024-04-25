/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:00:48 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/25 19:11:12 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"



int	main(int argc, char **argv)
{
	(void)argv;
	if (argc >= 5 && argc <= 6)
	{
		print_colours("Hello, World!\n", GREEN);
		print_colours("Hello, World!\n", MAGENTA);
	}
	else
		pri_error("Error: Wrong number of arguments 🤬");
	return (0);
}
