/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:45:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/04 18:28:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_tube(t_lem *lem, char *str)
{
	char	*tmp;
	t_room	*room1;
	t_room	*room2;

	tmp = ft_strchr(str, '-');
	*tmp = '\0';
	room1 = lem_get_room_name(lem, str);
	room2 = lem_get_room_name(lem, tmp + 1);
	if (room1 == NULL || room2 == NULL)
	{
		ft_strdel(&str);
		error_exit(lem);
	}
	room_add_connections(lem, room1, room2->index);
	room_add_connections(lem, room2, room1->index);
	*tmp = '-';
}

static void	parse_tubes(t_lem *lem, char *str)
{
	int	ret;

	buffer_putendl(str);
	if (!str || !is_valid_conn_format(str))
		error_exit(lem);
	add_tube(lem, str);
	ft_strdel(&str);
	while ((ret = get_next_line(0, &str)) > 0)
	{
		if (!is_valid_conn_format(str))
			break ;
		buffer_putendl(str);
		if (*str != '#')
			add_tube(lem, str);
		ft_strdel(&str);
	}
	if (str)
		ft_strdel(&str);
	while ((ret = get_next_line(0, &str)) > 0)
	{
		buffer_putendl(str);
		ft_strdel(&str);
	}
}

static void	add_room(t_lem *lem, char *str, int *flag, int index)
{
	char	**split;
	t_room	room;

	if (!(split = ft_strsplit(str, ' ')))
		error_exit(lem);
	room.name = split[0];
	room.index = index;
	room.x = ft_atoi(split[1]);
	room.y = ft_atoi(split[2]);
	room.flag = *flag;
	*flag = 0;
	room.ant = 0;
	room.connections = NULL;
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	ft_memdel((void**)&split);
	lem_add_room(lem, room);
}

static void	parse_rooms(t_lem *lem)
{
	char	*str;
	int		index;
	int		ret;
	int		flag;

	flag = 0;
	index = 1;
	while ((ret = get_next_line(0, &str)) > 0)
	{
		if (!is_valid_room_format(str))
			break ;
		buffer_putendl(str);
		if (ft_strequ(str, "##start"))
			flag = LEM_START;
		else if (ft_strequ(str, "##end"))
			flag = LEM_END;
		if (*str != '#')
			add_room(lem, str, &flag, index++);
		ft_strdel(&str);
	}
	if (ret == -1)
		error_exit(lem);
	parse_tubes(lem, str);
}

void		parse_lemin(t_lem *lem)
{
	char	*str;

	if (get_next_line(0, &str) != 1 || !ft_strisnumber(str))
		error_exit(NULL);
	lem->ant_count = ft_atoi(str);
	buffer_putendl(str);
	ft_strdel(&str);
	parse_rooms(lem);
}
