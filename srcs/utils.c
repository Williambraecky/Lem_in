/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:43:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/08 23:14:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_connections(t_lem *lem, int id, size_t dist)
{
	t_room	*room;
	size_t	i;

	room = &lem->rooms[id - 1];
	if (room_conn_contains(room, lem->end))
		return (1);
	i = 0;
	room->used = 1;
	room->dist = dist;
	while (room->connections[i])
	{
		if (lem->rooms[room->connections[i] - 1].used == 0)
			if (check_connections(lem, room->connections[i], dist + 1))
				return (1);
		i++;
	}
	return (0);
}

int			lem_is_valid(t_lem *lem)
{
	if (!lem->rooms)
		return (0);
	if (lem->start == 0 || lem->end == 0 || lem->ant_count <= 0)
		return (0);
	if (lem->rooms[lem->start - 1].nb_conn == 0)
		return (0);
	if (lem->rooms[lem->end - 1].nb_conn == 0)
		return (0);
	if (!check_connections(lem, lem->start, 1))
		return (0);
	reset_room_used(lem);
	return (1);
}

void		del_path(void *elem, size_t content_size)
{
	(void)content_size;
	free(*(void**)elem);
	free(elem);
}

void		move_ant(t_room *from, t_room *to)
{
	if (from->flag == LEM_START)
		from->ant++;
	buffer_putchar('L');
	buffer_putnbr(from->ant);
	buffer_putchar('-');
	buffer_putstr(to->name);
	buffer_putchar(' ');
	if (from->flag == LEM_START)
	{
		if (to->flag == LEM_END)
			to->ant++;
		else
			to->ant = from->ant;
	}
	else if (to->flag == LEM_END)
	{
		to->ant++;
		from->ant = 0;
	}
	else
	{
		to->ant = from->ant;
		from->ant = 0;
	}
}

void		print_path(t_lem *lem, t_paths path)
{
	size_t	i;

	i = 1;
	while (path[i])
	{
		ft_printf("%s", lem->rooms[path[i++] - 1].name);
		if (path[i])
			ft_printf("->");
	}
	ft_printf("\n");
}
