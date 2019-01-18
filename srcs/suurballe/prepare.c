/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:43:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/18 16:50:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** TODO: maybe move to suurballe.c
*/

void	prepare_map(t_lem *lem)
{
	t_room	*current;
	size_t	i;

	i = 0;
	while (i < lem->nb_rooms)
	{
		current = &lem->rooms[i];
		if (!(current->origin = ft_memdup(current->connections,
			sizeof(*(current->origin)) * (current->nb_conn))))
			error_exit(lem);
		current->origin_conn = current->nb_conn;
		current->used = 0;
		i++;
	}
}
