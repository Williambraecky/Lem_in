/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:32:50 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 14:46:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	lem_pathlen(t_lem *lem)
{
	size_t	i;

	i = 0;
	if (!lem->paths)
		return (i);
	while (lem->paths[i])
		i++;
	return (i);
}

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

t_paths	path_add(t_lem *lem, t_paths path, int room_index)
{
	t_paths	new;
	size_t	pathlen;

	pathlen = path_len(path);
	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * (pathlen + 2))))
		error_exit(lem);
	new[pathlen] = room_index;
	while (pathlen--)
		new[pathlen] = path[pathlen];
	return (new);
}
