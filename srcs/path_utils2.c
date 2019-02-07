/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:16:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/07 13:34:26 by wbraeckm         ###   ########.fr       */
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

	if (path1 == path2)
		return (1);
	len = path2[0];
	while (len-- > 2)
		if (path_passes_through(path1, path2[len]))
			return (1);
	return (0);
}

int		calc_len(t_paths path)
{
	int	len;
	int	i;

	len = path[0];
	i = 1;
	while (i - 1 < path[0])
	{
		if (path[i] & REVERSE_FLAG)
			len--;
		i++;
	}
	return (len);
}

int		cmp_path(t_paths *a, t_paths *b)
{
	return (ft_intcmp(calc_len(*a), calc_len(*b)));
}
