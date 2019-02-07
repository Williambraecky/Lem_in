/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:43:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/07 13:41:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	reset_map(t_lem *lem)
{
	t_room	*current;
	size_t	i;

	i = 0;
	while (i < lem->nb_rooms)
	{
		current = &lem->rooms[i];
		ft_memcpy(current->connections, current->origin,
			sizeof(*(current->origin)) * (current->origin_conn));
		current->nb_conn = current->origin_conn;
		current->used = 0;
		current->reverse = -1;
		i++;
	}
}

void	prepare_suurballe(t_lem *lem)
{
	size_t	i;
	int		j;

	if (!lem->paths)
		return ;
	i = 0;
	while (i < lem->nb_paths)
	{
		j = 1;
		while (j < lem->paths[i][0])
		{
			room_del_connections(&lem->rooms[lem->paths[i][j]],
			lem->paths[i][j + 1]);
			lem->rooms[lem->paths[i][j + 1]].reverse = lem->paths[i][j];
			j++;
		}
		i++;
	}
}
