/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:32:50 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/08 14:04:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	lem_pathlen(t_lem *lem)
{
	return (lem->nb_paths);
}

/*
** TODO: implement len at start of path? len->start->...->end ??
** 75K+ calls on test20000
*/

size_t	path_len(t_paths path)
{
	size_t	i;

	i = 0;
	if (!path)
		return (i);
	while (path[i])
		i++;
	return (i);
}

int		path_passes_through(t_paths path, int room_index)
{
	size_t	i;

	i = 0;
	if (!path)
		return (i);
	while (path[i])
		if (path[i++] == room_index)
			return (1);
	return (0);
}

t_paths	new_path(t_lem *lem, int start_index)
{
	t_paths new;

	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * 2)))
		error_exit(lem);
	new[0] = start_index;
	return (new);
}

t_paths	path_add(t_paths path, int room_index)
{
	t_paths	new;
	size_t	pathlen;

	pathlen = path_len(path);
	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * (pathlen + 2))))
		return (NULL);
	new[pathlen] = room_index;
	while (pathlen--)
		new[pathlen] = path[pathlen];
	return (new);
}
