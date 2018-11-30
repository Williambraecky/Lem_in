/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:21:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 18:50:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Improve logic
*/

static int	should_continue(t_lem *lem, t_list *list)
{
	(void)list;
	if (!lem->paths)
		return (1);
	if (lem->paths[0][0] == lem->start && lem->paths[0][1] == lem->end)
		return (0);
	if (calc_max_output(lem) >= lem->max_throughput)
		return (0);
	return (1);
}

static void	add_new_paths(t_lem *lem, t_list **list, t_paths path, t_room *room)
{
	size_t	conn_len;
	size_t	i;
	size_t	lstlen;
	t_paths	new;

	conn_len = room_connlen(room);
	i = 0;
	lstlen = ft_lstlen(*list);
	while (i < conn_len)
	{
		if (!path_passes_through(path, room->connections[i]))
		{
			new = path_add(lem, path, room->connections[i]);
			ft_lstpushback(list, &new, sizeof(t_paths));
			if (lstlen == ft_lstlen(*list))
			{
				ft_lstdel(list, del_path);
				error_exit(lem);
			}
			lstlen++;
		}
		i++;
	}
}

static void	process_path(t_lem *lem, t_list *elem)
{
	t_paths	path;

	path = (t_paths)*((void**)elem->content);
	if (path[path_len(path) - 1] == lem->end)
	{
		if (!(path = path_dup(path)))
		{
			ft_lstdel(&elem, del_path);
			error_exit(lem);
		}
		lem_path_add(lem, path);
	}
}

void		find_smallest_paths(t_lem *lem)
{
	t_list	*current_paths;
	t_paths	current;

	current_paths = NULL;
	current = new_path(lem, lem->start);
	add_new_paths(lem, &current_paths, current, &lem->rooms[lem->start] - 1);
	free(current);
	while (current_paths)
	{
		process_path(lem, current_paths);
		if (!should_continue(lem, current_paths))
			break ;
		current = (t_paths)*((void**)current_paths->content);
		add_new_paths(lem, &current_paths, current,
			&lem->rooms[current[path_len(current) - 1] - 1]);
		ft_lstpop(&current_paths, del_path);
	}
	if (current_paths)
		ft_lstdel(&current_paths, del_path);
}
