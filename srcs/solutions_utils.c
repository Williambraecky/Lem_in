/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:19:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 16:09:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t		compute_bandwidth(t_paths *paths, size_t len,
	size_t nb_lines)
{
	size_t	bandwidth;
	size_t	pathlen;
	size_t	i;

	if (!paths)
		return (0);
	i = 0;
	bandwidth = 0;
	while (i < len)
	{
		pathlen = paths[i][0] - 1;
		if (pathlen <= nb_lines)
			bandwidth += (nb_lines - pathlen + 1);
		i++;
	}
	return (bandwidth);
}

size_t		calc_needed_lines(t_lem *lem, t_paths *paths, size_t len)
{
	size_t	line;

	if (!paths)
		return (0);
	line = (size_t)paths[0][0] - 1;
	while (compute_bandwidth(paths, len, line) < lem->ant_count)
		line++;
	return (line);
}
