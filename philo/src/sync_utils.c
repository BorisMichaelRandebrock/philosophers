/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/31 18:41:44 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_long(type_mtx *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}
