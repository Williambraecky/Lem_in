/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/20 18:18:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_room(t_paths path, int room)
{
	int	i;

	i = 1;
	while (i - 1 < path[0])
	{
		if ((path[i] & NO_FLAG) == room)
			return (i);
		i++;
	}
	return (i);
}

t_paths		join_paths2(t_lem *lem, t_paths first,
	t_paths second, int join_room)
{
	t_paths	new;
	int		index_one;
	int		index_sec;
	int		len;
	int		i;

	index_one = find_room(first, join_room & NO_FLAG) + 1;
	index_sec = find_room(second, join_room & NO_FLAG) + 1;
	len = index_one + second[0] - index_sec;
	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * (len + 1))))
		error_exit(lem);
	new[0] = len;
	i = 1;
	while (i < index_one)
	{
		new[i] = first[i];
		i++;
	}
	while (index_sec <= second[0])
		new[i++] = second[index_sec++];
	return (new);
}

t_paths		join_paths(t_lem *lem, t_paths first,
	t_paths second, int join_room)
{
	t_paths	new;
	int		index_one;
	int		index_sec;
	int		len;
	int		i;

	index_one = find_room(first, join_room & NO_FLAG);
	index_sec = find_room(second, join_room & NO_FLAG);
	len = index_one + second[0] - index_sec;
	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * (len + 1))))
		error_exit(lem);
	new[0] = len;
	i = 1;
	while (i < index_one)
	{
		new[i] = first[i];
		i++;
	}
	while (index_sec <= second[0])
		new[i++] = second[index_sec++];
	return (new);
}

void		normalize_path(t_paths path)
{
	int	i;

	i = 1;
	while (i - 1 < path[0])
		path[i++] &= NO_FLAG;
}

int			is_path_clean(t_paths path)
{
	int	i;

	i = 1;
	while (i - 1 < path[0])
		if (path[i++] & REVERSE_FLAG)
			return (0);
	return (1);
}
