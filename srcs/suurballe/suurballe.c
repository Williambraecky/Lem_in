/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:17:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/18 17:31:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static void	reset_map(t_lem *lem)
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
		current->reverse = 0;
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
	while (lem->paths[i])
	{
		j = 1;
		while (j < lem->paths[i][0])
		{
			room_del_connections(&lem->rooms[lem->paths[i][j] - 1],
			lem->paths[i][j + 1]);
			lem->rooms[lem->paths[i][j + 1] - 1].reverse = lem->paths[i][j];
			j++;
		}
		i++;
	}
}

/*
** TODO: Connect paths containing negative weights before adding to lem;
** lem normalizes path
*/

void		suurballe(t_lem *lem)
{
	t_paths	last;

	last = bfs(lem);
	if (!last)
		return ;
	lem_path_add(lem, last, NULL);
	prepare_map(lem);
	print_path(lem, last);
	while (last)
	{
		prepare_suurballe(lem);
		last = bfs(lem);
		if (last)
		{
			lem_path_add(lem, last, NULL);
			print_path(lem, last);
			reset_map(lem);
		}
	}
}
