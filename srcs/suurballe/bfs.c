/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:11:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/06 15:44:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		calc_len(t_paths path)
{
	int	len;
	int	i;

	len = path[0];
	i = 1;
	while (i < path[0])
	{
		if (path[i] & REVERSE_FLAG)
		{
			if (!(path[i] & REVERSE_FLAG))
				len--;
			len--;
		}
		i++;
	}
	return (len);
}

static int		cmp_path(t_paths *a, t_paths *b)
{
	return (ft_intcmp(calc_len(*a), calc_len(*b)));
}

static void	lstsortinsert(t_list **begin_list, t_list *insert,
		int (*cmp)())
{
	t_list *current;
	t_list *prev;

	current = *begin_list;
	if (current == NULL || cmp(current->content, insert->content) > 0)
	{
		insert->next = current != NULL ? current->next : NULL;
		if (!current)
			*begin_list = insert;
		return ;
	}
	prev = current;
	while ((current = current->next) != NULL)
	{
		if (cmp(current->content, insert->content) > 0)
		{
			prev->next = insert;
			insert->next = current;
			return ;
		}
		prev = current;
	}
	prev->next = insert;
}


static void		add_new_path(t_lem *lem, t_list **list, t_paths path, int index)
{
	t_paths	new;
	t_list	*new_node;

	if (!(new = path_add(path, index))
		|| !(new_node = ft_lstnew(&new, sizeof(t_paths))))
	{
		ft_lstdel(list, del_path);
		error_exit(lem);
		return ;
	}
	lstsortinsert(list, new_node, cmp_path);
	// if (!(*list))
	// {
	// 	*list = new_node;
	// 	list[1] = new_node;
	// }
	// else if (index & REVERSE_FLAG)
	// {
	// 	new_node->next = list[0]->next;
	// 	list[0]->next = new_node;
	// 	if (new_node->next == NULL)
	// 		list[1] = new_node;
	// }
	// else
	// {
	// 	list[1]->next = new_node;
	// 	list[1] = new_node;
	// }
}

/*
** TODO: Handle negative links etc..
*/

static int		should_follow(t_paths path, t_room *check, t_room *from)
{
	if ((check->nb_conn < 2 && !check->reverse) || check->used != 0
		|| (from->reverse != -1 && from->reverse != check->index
			&& !(path[*path] & REVERSE_FLAG)))
		return (0);
	check->used++;
	if (from->reverse && from->reverse == check->index)
		return (2);
	return (1);
}

static t_paths	add_new_paths(t_lem *lem, t_list **list, t_paths path,
	t_room *room)
{
	size_t	i;
	t_paths	found;
	int		ret;

	if (!room->connections)
		return (NULL);
	if (room_conn_contains(room, lem->end))
	{
		if (!(found = path_add(path, lem->end)))
		{
			ft_lstdel(list, del_path);
			error_exit(lem);
		}
		return (found);
	}
	i = 0;
	while (i < room->nb_conn)
	{
		if ((ret = should_follow(path, &lem->rooms[room->connections[i]],
			room)))
			add_new_path(lem, list, path, ret == 2 ?
				room->connections[i] | REVERSE_FLAG : room->connections[i]);
		i++;
	}
	return (NULL);
}

t_paths			bfs(t_lem *lem)
{
	t_list	*paths[2];
	t_paths	current;
	t_paths	found;

	paths[0] = NULL;
	paths[1] = NULL;
	current = new_path(lem, lem->start);
	found = add_new_paths(lem, paths, current, &lem->rooms[lem->start]);
	free(current);
	// int min_len;
	while (*paths && !found)
	{
		current = (t_paths)*((void**)paths[0]->content);
		// if (calc_len(current) < min_len)
		// 	ft_printf("This is the problem\n");
		// else
		// 	min_len = calc_len(current);
		// ft_printf("TRYING ");
		// print_path(lem, current);
		found = add_new_paths(lem, paths, current,
			&lem->rooms[(current[*current] & NO_FLAG)]);
		ft_lstpop(paths, del_path);
	}
	if (*paths)
		ft_lstdel(paths, del_path);
	return (found);
}
