/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:15:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 15:01:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_valid_room_format(char *str)
{
	if (*str == '#')
		return (1);
	if (*str == 'L' || ft_strcountchar(str, ' ') != 2)
		return (0);
	while (*str != ' ')
		str++;
	str += (*str == '-' || *str == '+') + 1;
	while (*str != ' ')
		if (!ft_isdigit(*str++))
			return (0);
	str += (*str == '-' || *str == '+') + 1;
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int		is_valid_conn_format(char *str)
{
	char	*tmp;

	if (ft_strcountchar(str, '-') != 1)
		return (0);
	tmp = ft_strchr(str, '-');
	return (str != tmp && *(tmp + 1) != '\0');
}

size_t	room_connlen(t_room *room)
{
	size_t	i;

	i = 0;
	if (!room->connections)
		return (i);
	while (room->connections[i])
		i++;
	return (i);
}

int		room_conn_contains(t_room *room, int id)
{
	size_t	len;

	len = room_connlen(room);
	if (!room->connections)
		return (0);
	while (room->connections[len])
		if (room->connections[len--] == id)
			return (1);
	return (0);
}

void	room_add_connections(t_lem *lem, t_room *room, int id)
{
	int		*new;
	size_t	len;

	if (room_conn_contains(room, id))
		return ;
	len = room_connlen(room);
	if (!(new = (int*)ft_memalloc(sizeof(*new) * (len + 2))))
		error_exit(lem);
	new[len] = id;
	while (len--)
		new[len] = room->connections[len];
	free(room->connections);
	room->connections = new;
}
