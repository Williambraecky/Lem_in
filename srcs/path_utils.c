/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:32:50 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/19 18:28:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_passes_through(t_paths path, int room_index)
{
	int	i;

	if (!path)
		return (1);
	i = 1;
	while (i - 1 < path[0])
		if (path[i++] == room_index)
			return (1);
	return (0);
}

t_paths	new_path(t_lem *lem, int start_index)
{
	t_paths new;

	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * 2)))
		error_exit(lem);
	new[0] = 1;
	new[1] = start_index;
	return (new);
}

t_paths	path_add(t_paths path, int room_index)
{
	t_paths	new;
	size_t	pathlen;

	pathlen = path[0] + 1;
	if (!(new = (t_paths)ft_memalloc(sizeof(*new) * (pathlen + 1))))
		return (NULL);
	new[0] = pathlen;
	new[pathlen] = room_index;
	while (pathlen-- > 1)
		new[pathlen] = path[pathlen];
	return (new);
}
