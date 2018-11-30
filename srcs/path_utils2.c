/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:16:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 18:49:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Compares every point between start and end /!\ unusable if it's not a full
** path
*/

int		path_collide(t_paths path1, t_paths path2)
{
	size_t	len;

	len = path_len(path2) - 1;
	while (len-- > 1)
		if (path_passes_through(path1, path2[len]))
			return (1);
	return (0);
}

int		calc_max_output(t_lem *lem)
{
	int		i;
	int		l;
	size_t	len;
	size_t	j;
	size_t	k;

	i = 0;
	len = lem_pathlen(lem);
	j = 0;
	k = 0;
	while (j < len)
	{
		k = 0;
		l = 0;
		while (k < len)
		{
			if (k == j || !path_collide(lem->paths[j], lem->paths[k]))
				l++;
			k++;
		}
		if (l > i)
			i = l;
		j++;
	}
	return (i);
}
