/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:45:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 17:33:23 by wbraeckm         ###   ########.fr       */
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
		error_exit(lem);
	room_add_connections(lem, room1, room2->index);
	room_add_connections(lem, room2, room1->index);
	*tmp = '-';
}

static void	parse_tubes(t_lem *lem)
{
	int	ret;

	create_hash_table(lem);
	if (!lem->line || !is_valid_conn_format(lem->line))
		error_exit(lem);
	add_tube(lem, lem->line);
	ft_strdel(&lem->line);
	while ((ret = get_next_line(lem->fd, &lem->line)) > 0)
	{
		if (!is_valid_conn_format(lem->line))
			break ;
		if (*lem->line != '#')
			add_tube(lem, lem->line);
		ft_strdel(&lem->line);
	}
	if (lem->line)
		ft_strdel(&lem->line);
	while ((ret = get_next_line(lem->fd, &lem->line)) > 0)
		ft_strdel(&lem->line);
}

static void	add_room(t_lem *lem, char *str, int *flag, int index)
{
	char	**split;
	t_room	room;

	if (!(split = ft_strsplit(str, ' ')))
		error_exit(lem);
	ft_memset(&room, 0, sizeof(room));
	room.reverse = -1;
	room.name = split[0];
	room.index = index;
	room.x = ft_atoi(split[1]);
	room.y = ft_atoi(split[2]);
	room.flag = *flag;
	if ((*flag == LEM_START && lem->start != -1) ||
		(*flag == LEM_END && lem->end != -1))
		error_exit(lem);
	*flag = 0;
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	ft_memdel((void**)&split);
	lem_add_room(lem, room);
}

static void	parse_rooms(t_lem *lem)
{
	int		ret;
	int		flag;

	flag = 0;
	while ((ret = get_next_line(lem->fd, &lem->line)) > 0)
	{
		if (!is_valid_room_format(lem->line))
			break ;
		if (ft_strequ(lem->line, "##start"))
			flag = LEM_START;
		else if (ft_strequ(lem->line, "##end"))
			flag = LEM_END;
		if (*lem->line != '#')
			add_room(lem, lem->line, &flag, lem->nb_rooms++);
		ft_strdel(&lem->line);
	}
	if (ret == -1)
		error_exit(lem);
	parse_tubes(lem);
}

void		parse_lemin(t_lem *lem)
{
	int	ret;

	while ((ret = get_next_line(lem->fd, &lem->line)) == 1)
	{
		if (!ft_strisnumber(lem->line) && lem->line[0] != '#')
			break ;
		else if (ft_strisnumber(lem->line))
		{
			if (lem->line[0] == '-')
				error_exit(lem);
			lem->ant_count = ft_atol(lem->line);
			break ;
		}
		ft_strdel(&lem->line);
	}
	if (ret == -1)
		error_exit(lem);
	lem->ant_count = ft_atol(lem->line);
	ft_strdel(&lem->line);
	parse_rooms(lem);
}
