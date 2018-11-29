/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:48:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/29 17:46:25 by wbraeckm         ###   ########.fr       */
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

t_room	*lem_get_room_id(t_lem *lem, int id)
{
	if ((size_t)id >= lem_roomlen(lem))
		return (NULL);
	return (&lem->rooms[id - 1]);
}

t_room	*lem_get_room_name(t_lem *lem, char *str)
{
	size_t	i;

	i = 0;
	while (lem->rooms[i].name)
	{
		if (ft_strequ(lem->rooms[i].name, str))
			return (&(lem->rooms[i]));
		i++;
	}
	return (NULL);
}

void	lem_add_room(t_lem *lem, t_room room)
{
	t_room	*new;
	size_t	len;

	len = lem_roomlen(lem);
	if (!(new = (t_room*)ft_memalloc(sizeof(*(lem->rooms)) * (len + 2))))
		error_exit(lem);
	if (lem->rooms)
		ft_memcpy(new, lem->rooms, sizeof(*(lem->rooms)) * (len + 1));
	if (room.flag == LEM_START)
		lem->start = room.index;
	else if (room.flag == LEM_END)
		lem->end = room.index;
	new[len] = room;
	free(lem->rooms);
	lem->rooms = new;
}
