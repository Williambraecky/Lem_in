/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:19:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/18 15:15:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t		compute_bandwidth(t_lem *lem, size_t nb_lines)
{
	size_t	bandwidth;
	size_t	pathlen;
	size_t	i;

	if (!lem->solve)
		return (0);
	i = 0;
	bandwidth = 0;
	while (lem->solve[i])
	{
		pathlen = path_len(lem->solve[i]) - 1;
		if (pathlen <= nb_lines)
			bandwidth += (nb_lines - pathlen + 1);
		i++;
	}
	return (bandwidth);
}
