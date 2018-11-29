/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:33:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/29 17:21:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>

# define LEM_START 1
# define LEM_END 2

typedef int*	t_paths;

typedef struct s_room	t_room;
struct		s_room
{
	char	*name;
	int		index;
	int		x;
	int		y;
	int		flag;
	int		*connections;
};

typedef struct s_lem	t_lem;
struct		s_lem
{
	t_room	*rooms;
	t_paths	*paths;
	int		ant_count;
	int		start;
	int		end;
};

/*
** Parse
*/
void		parse_lemin(t_lem *lem);

/*
** Utils
*/
void		error_exit(t_lem *lem);
void		lem_add_room(t_lem *lem, t_room room);
size_t		lem_roomlen(t_lem *lem);
t_room		*lem_get_room_id(t_lem *lem, int id);
t_room		*lem_get_room_name(t_lem *lem, char *str);
void		room_add_connections(t_lem *lem, t_room *room, int id);
size_t		room_connlen(t_room *room);
int			is_valid_room_format(char *str);
int			is_valid_conn_format(char *str);
int			lem_is_valid(t_lem *lem);

/*
** Free
*/
void		free_rooms(t_lem *lem);
void		free_paths(t_lem *lem);

#endif
