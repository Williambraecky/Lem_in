/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:15:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/19 18:04:37 by wbraeckm         ###   ########.fr       */
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

	if (*str == '#')
		return (1);
	if (ft_strcountchar(str, '-') != 1)
		return (0);
	tmp = ft_strchr(str, '-');
	return (str != tmp && *(tmp + 1) != '\0');
}

int		room_conn_contains(t_room *room, int id)
{
	size_t	i;

	if (!room->connections)
		return (0);
	i = 0;
	while (i < room->nb_conn)
		if (room->connections[i++] == id)
			return (1);
	return (0);
}

void	room_add_connections(t_lem *lem, t_room *room, int id)
{
	int		*new;

	if (room_conn_contains(room, id))
		return ;
	if (room->max_conn == 0)
		room->max_conn = LEM_CONN_START;
	if (!room->connections || room->nb_conn == room->max_conn)
	{
		if (room->connections)
			room->max_conn *= 2;
		if (!(new = (int*)ft_realloc(room->connections,
			sizeof(*new) * (room->max_conn / 2),
			sizeof(*new) * (room->max_conn + 1))))
			error_exit(lem);
		room->connections = new;
	}
	room->connections[room->nb_conn++] = id;
}

void	room_del_connections(t_room *room, int id)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < room->nb_conn)
	{
		if (room->connections[i] != id)
			room->connections[j++] = room->connections[i];
		i++;
	}
	room->connections[j] = 0;
	room->nb_conn--;
}
