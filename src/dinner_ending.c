/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_ending.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:42:32 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/01 14:08:31 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

void	restaurant_closing(t_table *table)
{
	print_colours("We hope you have enjoied the soirée, and shall\n"
		 "		be delighted to be seeing you again very soon...\n", YELLOW);
		 printf("👋🏻\n");
	free(table->forks);
	free(table->philos);
}
