/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:21:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/02 02:08:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Improve logic
*/

static int	should_continue(t_lem *lem, t_list *list)
{
	if (!list)
		return (0);
	if (!lem->paths)
		return (1);
	if (path_len((t_paths)*(void**)list->content) - 1 +
		lem->current_max_throughput > (size_t)lem->ant_count)
		return (0);
	if (lem->paths[0][0] == lem->start && lem->paths[0][1] == lem->end)
		return (0);
	if (lem->current_max_throughput >= lem->max_throughput)
		return (0);
	return (1);
}
//
// static int	should_add(t_list *list, t_paths path, int room_index)
// {
// 	t_paths	current;
//
// 	if (path_passes_through(path, room_index))
// 		return (0);
// 	while (list)
// 	{
// 		current = (t_paths)*((void**)list->content);
// 		if (current[path_len(current) - 1] == room_index)
// 			return (0);
// 		list = list->next;
// 	}
// 	return (1);
// }

// static void	process_path(t_lem *lem, t_list *elem)
// {
// 	t_paths	path;
//
// 	path = (t_paths)*((void**)elem->content);
// 	if (path[path_len(path) - 1] == lem->end)
// 	{
// 		if (!(path = path_dup(path)))
// 		{
// 			ft_lstdel(&elem, del_path);
// 			error_exit(lem);
// 		}
// 		lem_path_add(lem, path);
// 		lem->current_max_throughput = calc_max_output(lem);
// 	}
// }

static void	process_path(t_lem *lem, t_list **list, t_paths path)
{
	t_paths	new;

	if (!(new = path_add(lem, path, lem->end)))
	{
		ft_lstdel(list, del_path);
		error_exit(lem);
	}
	lem_path_add(lem, new);
	lem->current_max_throughput = calc_max_output(lem);
}

static void add_new_path(t_lem *lem, t_list **list, t_paths path, int index)
{
	size_t	lstlen;
	t_paths	new;

	lstlen = ft_lstlen(*list);
	new = path_add(lem, path, index);
	ft_lstpushback(list, &new, sizeof(t_paths));
	if (lstlen == ft_lstlen(*list))
	{
		ft_lstdel(list, del_path);
		error_exit(lem);
	}
}

static void	add_new_paths(t_lem *lem, t_list **list, t_paths path, t_room *room)
{
	size_t	conn_len;
	size_t	i;

	if (room->index == lem->end)
		return ;
	conn_len = room_connlen(room);
	i = 0;
	while (i < conn_len)
	{
		if ((room_connlen(&lem->rooms[room->connections[i] - 1]) > 1 ||
			room->connections[i] == lem->end) &&
			!path_passes_through(path, room->connections[i]))
		{
			if (room->connections[i] == lem->end)
				process_path(lem, list, path);
			else
				add_new_path(lem, list, path, room->connections[i]);
		}
		i++;
	}
}

void		find_smallest_paths(t_lem *lem)
{
	t_list	*current_paths;
	t_paths	current;
	size_t	i;

	current_paths = NULL;
	current = new_path(lem, lem->start);
	add_new_paths(lem, &current_paths, current, &lem->rooms[lem->start - 1]);
	free(current);
	i = 0;
	while (should_continue(lem, current_paths))
	{
		current = (t_paths)*((void**)current_paths->content);
		//ft_printf("%zu L : %d l : %zu m : %zu\n",
		//	i++, lem_pathlen(lem), path_len(current), lem->current_max_throughput);
		add_new_paths(lem, &current_paths, current,
			&lem->rooms[current[path_len(current) - 1] - 1]);
		ft_lstpop(&current_paths, del_path);
	}
	ft_printf("null? %d max %d\n", current_paths == NULL, lem->current_max_throughput);
	if (current_paths != NULL)
		ft_lstdel(&current_paths, del_path);
}
