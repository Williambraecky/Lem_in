/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:21:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/19 18:13:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	partition(t_paths *paths, size_t low, size_t high)
{
	int		pivot;
	size_t	i;
	size_t	left;

	pivot = paths[low][0];
	left = low;
	i = low + 1;
	while (i < high)
	{
		if (paths[i][0] < pivot)
			ft_memswap(&paths[i], &paths[++left], sizeof(paths[0]));
		i++;
	}
	ft_memswap(&paths[low], &paths[left], sizeof(paths[0]));
	return (left);
}

static void		quicksort(t_paths *paths, size_t low, size_t high)
{
	size_t pivot;

	if (low < high)
	{
		pivot = partition(paths, low, high);
		quicksort(paths, low, pivot);
		quicksort(paths, pivot + 1, high);
	}
}

void			sort_paths(t_paths *paths, size_t nb_paths)
{
	if (!paths)
		return ;
	quicksort(paths, 0, nb_paths);
}
