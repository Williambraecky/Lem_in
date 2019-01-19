/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:21:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/19 18:09:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** DEPRECATED
*/

// /*
// ** TODO: Improve logic
// */
// static int	should_continue(t_lem *lem, t_list *list)
// {
// 	size_t	lowest;
//
// 	if (!list)
// 		return (0);
// 	if (!lem->paths)
// 		return (1);
// 	if (lem->paths[0][0] == lem->start && lem->paths[0][1] == lem->end)
// 		return (0);
// 	if (lem->current_max_throughput >= lem->max_throughput)
// 		return (0);
// 	if (lem->current_bandwidth >= lem->ant_count)
// 		return (0);
// 	lowest = path_len((t_paths)*(void**)list->content);
// 	if (lowest > lem->current_lines &&
// 		compute_bandwidth(lem, lowest) >= lem->ant_count)
// 	{
// 		lem->current_lines = lowest;
// 		lem->current_bandwidth = compute_bandwidth(lem, lowest);
// 		return (0);
// 	}
// 	if (lowest - 1 + lem->current_max_throughput > lem->ant_count)
// 		return (0);
// 	return (1);
// }
//
// static void	process_path(t_lem *lem, t_list **list, t_paths path)
// {
// 	t_paths	new;
//
// 	if (!(new = path_add(path, lem->end)))
// 	{
// 		ft_lstdel(list, del_path);
// 		error_exit(lem);
// 	}
// 	lem_path_add(lem, new, list);
// 	if ((lem->current_max_throughput = calc_max_output(lem)) == -1)
// 	{
// 		ft_lstdel(list, del_path);
// 		error_exit(lem);
// 	}
// }
//
// /*
// ** TODO: Verify that new_node is not NULL
// */
//
// static void	add_new_path(t_lem *lem, t_list **list, t_paths path, int index)
// {
// 	t_paths	new;
// 	t_list	*new_node;
//
// 	if (!(new = path_add(path, index)))
// 	{
// 		ft_lstdel(list, del_path);
// 		error_exit(lem);
// 	}
// 	new_node = ft_lstnew(&new, sizeof(t_paths));
// 	if (!(*list))
// 		*list = new_node;
// 	else
// 		list[1]->next = new_node;
// 	list[1] = new_node;
// }
//
// static void	add_new_paths(t_lem *lem, t_list **list, t_paths path, t_room *room)
// {
// 	size_t	i;
//
// 	if (!room->connections)
// 		return ;
// 	if (room_conn_contains(room, lem->end))
// 	{
// 		process_path(lem, list, path);
// 		return ;
// 	}
// 	i = 0;
// 	while (room->connections[i])
// 	{
// 		if (lem->rooms[room->connections[i] - 1].nb_conn > 1
// 		&& !path_passes_through(path, room->connections[i]))
// 			add_new_path(lem, list, path, room->connections[i]);
// 		i++;
// 	}
// }
//
// void		find_smallest_paths(t_lem *lem)
// {
// 	t_list	*current_paths[2];
// 	t_paths	current;
// 	size_t	i;
//
// 	current_paths[0] = NULL;
// 	current_paths[1] = NULL;
// 	current = new_path(lem, lem->start);
// 	add_new_paths(lem, current_paths, current, &lem->rooms[lem->start - 1]);
// 	free(current);
// 	i = 0;
// 	while (should_continue(lem, current_paths[0]))
// 	{
// 		current = (t_paths)*((void**)current_paths[0]->content);
// 		// ft_printf("%zu L : %d l : %zu m : %zu b: %zu\n", i++,
// 		// lem_pathlen(lem), path_len(current), lem->current_max_throughput,
// 		// lem->current_bandwidth);
// 		add_new_paths(lem, current_paths, current,
// 			&lem->rooms[current[path_len(current)] - 1]);
// 		ft_lstpop(current_paths, del_path);
// 	}
// 	if (current_paths[0] != NULL)
// 		ft_lstdel(current_paths, del_path);
// }
