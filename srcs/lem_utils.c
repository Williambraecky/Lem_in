/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:48:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/06 21:41:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	lem_roomlen(t_lem *lem)
{
	size_t	i;

	i = 0;
	if (!lem->rooms)
		return (i);
	while (lem->rooms[i].name)
		i++;
	return (i);
}

size_t	simple_hash(char *str)
{
	size_t	hash;

	hash = 17;
	while (*str)
		hash = hash * 31 + *str++;
	return (hash);
}

t_room	*lem_get_room_name(t_lem *lem, char *str, int i)
{
	t_room	*rooms;
	size_t	hash;

	if (lem->last_1 && ft_strcmp(lem->last_1->name, str) == 0)
		return (lem->last_1);
	else if (lem->last_2 && ft_strcmp(lem->last_2->name, str) == 0)
		return (lem->last_2);
	hash = simple_hash(str);
	rooms = lem->rooms;
	while (rooms->name)
	{
		if (hash == rooms->hash && !ft_strcmp(rooms->name, str))
		{
			if (i == 1)
				lem->last_1 = rooms;
			else if (i == 2)
				lem->last_2 = rooms;
			return (rooms);
		}
		rooms++;
	}
	return (NULL);
}

/*
** TODO: Handle rooms room with same x y or name is already present
*/

void	lem_add_room(t_lem *lem, t_room room)
{
	t_room	*new;
	size_t	i;

	room.hash = simple_hash(room.name);
	if (lem->max_rooms == 0)
		lem->max_rooms = LEM_ROOM_START;
	if (!lem->rooms || (size_t)room.index > lem->max_rooms)
	{
		if (lem->rooms)
			lem->max_rooms *= 2;
		if (!(new = (t_room*)ft_memalloc(sizeof(*new) * (lem->max_rooms + 1))))
			error_exit(lem);
		i = 0;
		if (lem->rooms)
			while (lem->rooms[i].name)
			{
				new[i] = lem->rooms[i];
				i++;
			}
		ft_memdel((void**)&lem->rooms);
		lem->rooms = new;
	}
	lem->rooms[room.index - 1] = room;
	if (room.flag == LEM_START)
		lem->start = room.index;
	else if (room.flag == LEM_END)
		lem->end = room.index;
}

void	lem_path_add(t_lem *lem, t_paths paths, t_list **list)
{
	t_paths	*new;
	size_t	len;

	len = lem_pathlen(lem);
	if (!(new = (t_paths*)ft_memalloc(sizeof(*new) * (len + 2))))
	{
		ft_lstdel(list, del_path);
		error_exit(lem);
	}
	new[len] = paths;
	while (len--)
		new[len] = lem->paths[len];
	free(lem->paths);
	lem->paths = new;
}
