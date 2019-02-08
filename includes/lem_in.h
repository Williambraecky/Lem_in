/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:33:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 16:09:38 by wbraeckm         ###   ########.fr       */
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
# define LEM_ROOM_START 16
# define LEM_CONN_START 3
# define LEM_COMBO_START 10
# define DICT_LEN_START 50
# define MAX_PATHS 50

# define REVERSE_FLAG (1 << 31)
# define NO_FLAG 0x7FFFFFFF

# define VERBOSE_FLAG (1 << 0)
# define SHOW_FLAG (1 << 1)
# define HIDE_FLAG (1 << 2)

typedef int*	t_paths;

typedef struct s_room	t_room;
struct		s_room
{
	char	*name;
	size_t	hash;
	int		used;
	int		index;
	int		x;
	int		y;
	int		flag;
	size_t	ant;
	int		*connections;
	int		*origin;
	size_t	max_conn;
	size_t	nb_conn;
	size_t	origin_conn;
	int		reverse;
};

typedef struct s_lem	t_lem;
struct		s_lem
{
	int		fd;
	int		autonomy;
	int		max_paths;
	int		mode;
	int		flags;
	char	*line;
	char	**dictionary;
	size_t	dict_len;
	size_t	max_dict_len;
	t_room	*rooms;
	t_room	**hash_table;
	size_t	max_rooms;
	size_t	nb_rooms;
	t_paths	*paths;
	size_t	nb_paths;
	t_paths	*copy;
	size_t	copy_len;
	size_t	ant_count;
	size_t	current_lines;
	int		start;
	int		end;
	t_paths	(*algo)(t_lem *lem);
};

/*
** TODO: reorganize prototypes
*/

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
t_room		*lem_get_room_name(t_lem *lem, char *str);
void		room_add_connections(t_lem *lem, t_room *room, int id);
int			is_valid_room_format(char *str);
int			is_valid_conn_format(char *str);
int			lem_is_valid(t_lem *lem);
t_paths		path_add(t_paths path, int index);
int			path_passes_through(t_paths path, int room_index);
void		del_path(void *elem, size_t content_size);
int			room_conn_contains(t_room *room, int id);
void		lem_path_add(t_lem *lem, t_paths paths, t_list **list);
t_paths		new_path(t_lem *lem, int start_index);
void		print_path(t_lem *lem, t_paths path);
int			calc_max_output(t_lem *lem);
int			path_collide(t_paths path1, t_paths path2);
void		move_ant(t_lem *lem, t_room *from, t_room *to);
size_t		compute_bandwidth(t_paths *paths, size_t len,
	size_t nb_lines);
size_t		simple_hash(char *str);
void		sort_paths(t_paths *paths, size_t nb_paths);
void		reset_room_used(t_lem *lem);
t_paths		bfs(t_lem *lem);
t_paths		reverse_bfs(t_lem *lem);
void		room_del_connections(t_room *room, int id);
void		prepare_map(t_lem *lem);
void		suurballe(t_lem *lem);
void		normalize_path(t_paths path);
int			is_path_clean(t_paths path);
t_paths		handle_conflict(t_lem *lem, t_paths path);
t_paths		join_paths(t_lem *lem, t_paths first,
	t_paths second, int join_room);
t_paths		join_paths2(t_lem *lem, t_paths first,
	t_paths second, int join_room);
size_t		calc_needed_lines(t_lem *lem, t_paths *paths, size_t len);
void		create_hash_table(t_lem *lem);
int			calc_len(t_paths path);
int			cmp_path(t_paths *a, t_paths *b);
void		reset_map(t_lem *lem);
void		prepare_suurballe(t_lem *lem);
void		read_lem_opt(t_lem *lem, int argc, char **argv);
void		error_usage(t_lem *lem);
void		error_message(t_lem *lem, char *msg);
void		read_dictionary(t_lem *lem, int *i, char **argv);
void		free_copy(t_lem *lem);
void		free_paths(t_lem *lem);

/*
** Free
*/

void		del_combo(void *elem, size_t content_size);
void		free_lem(t_lem *lem);

/*
** Buffer
*/

void		buffer_flush(void);
void		buffer_putchar(char c);
void		buffer_putstr(char *str);
void		buffer_putendl(char *str);
void		buffer_putnbr(int i);

#endif
