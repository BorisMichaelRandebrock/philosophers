/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_ending.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:42:32 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/29 14:46:02 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "colours.h"

void	restaurant_closing(t_table *table)
{
	free(table->forks);
	free(table->philos);
}
