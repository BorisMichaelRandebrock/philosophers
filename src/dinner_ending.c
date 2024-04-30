/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_ending.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:42:32 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/30 17:10:56 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

void	restaurant_closing(t_table *table)
{
	print_colours("We hope you have enjoied the soirée, and are\n"
		 "		looking forward to be seeing you again "
		 "very soon...\n", YELLOW);
		 printf("👋🏻\n");
	free(table->forks);
	free(table->philos);
}
