/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:48:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/08 14:01:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	simple_hash(char *str)
{
	size_t	hash;

	hash = 17;
	while (*str)
		hash = hash * 31 + *str++;
	return (hash);
}

t_room	*lem_get_room_name(t_lem *lem, char *str)
{
	size_t	hash;
	size_t	j;
	size_t	orig;

	hash = simple_hash(str);
	j = hash % lem->nb_rooms;
	orig = j;
	while (1)
	{
		if (hash == lem->hash_table[j]->hash &&
			ft_strcmp(lem->hash_table[j]->name, str) == 0)
			return (lem->hash_table[j]);
		j++;
		if (j == orig)
			break;
		if (j == lem->nb_rooms)
			j = 0;
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
	lem->nb_paths++;
	new[len] = paths;
	while (len--)
		new[len] = lem->paths[len];
	free(lem->paths);
	lem->paths = new;
}
