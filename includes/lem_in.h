/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:33:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/04 18:33:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>

# define LEM_START 1
# define LEM_END 2
# define LEM_BUFFER_SIZE 4096

typedef int*	t_paths;

typedef struct s_room	t_room;
struct		s_room
{
	char	*name;
	int		index;
	int		x;
	int		y;
	int		flag;
	int		ant;
	int		*connections;
};

typedef struct s_lem	t_lem;
struct		s_lem
{
	t_room	*rooms;
	t_paths	*paths;
	int		ant_count;
	int		max_throughput;
	int		current_max_throughput;
	int		start;
	int		end;
};

/*
** Algo
*/

void		find_smallest_paths(t_lem *lem);

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
size_t		lem_pathlen(t_lem *lem);
size_t		path_len(t_paths path);
t_paths		path_add(t_paths path, int index);
int			path_passes_through(t_paths path, int room_index);
void		del_path(void *elem, size_t content_size);
int			room_conn_contains(t_room *room, int id);
void		lem_path_add(t_lem *lem, t_paths paths, t_list **list);
t_paths		new_path(t_lem *lem, int start_index);
t_paths		path_dup(t_paths path);
void		print_path(t_lem *lem, t_paths path);
int			calc_max_output(t_lem *lem);
int			path_collide(t_paths path1, t_paths path2);
void		move_ant(t_room *from, t_room *to);

/*
** Free
*/

void		free_rooms(t_lem *lem);
void		free_paths(t_lem *lem);

/*
** Buffer
*/

void		buffer_flush(void);
void		buffer_putchar(char c);
void		buffer_putstr(char *str);
void		buffer_putendl(char *str);
void		buffer_putnbr(int i);

#endif
