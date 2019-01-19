/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/19 16:02:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	normalize_path(t_paths path)
{
	int	i;

	i = 1;
	while (i - 1 < path[0])
		path[i++] &= NO_FLAG;
}

int		is_path_clean(t_paths path)
{
	int	i;

	i = 1;
	while (i - 1 < path[0])
		if (path[i++] & REVERSE_FLAG)
			return (0);
	return (1);
}
