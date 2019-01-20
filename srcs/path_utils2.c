/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:16:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/20 18:24:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Compares every point between start and end /!\ unusable if it's not a full
** path
*/

int			path_collide(t_paths path1, t_paths path2)
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
//
// static int	current_size(t_paths *paths)
// {
// 	int	i;
//
// 	i = 0;
// 	while (paths[i])
// 		i++;
// 	return (i);
// }
//
// static void	add_to_paths(t_paths *paths, t_paths path)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (paths[i])
// 		i++;
// 	paths[i] = path;
// }
//
// static void	check_throughput(t_lem *lem, t_paths *paths, size_t len)
// {
// 	size_t	j;
// 	size_t	k;
// 	int		collide;
//
// 	j = 0;
// 	while (j < len)
// 	{
// 		k = 0;
// 		collide = 0;
// 		while (!collide && paths[k])
// 		{
// 			if (path_collide(lem->paths[j], paths[k]))
// 				collide = 1;
// 			k++;
// 		}
// 		if (!collide)
// 			add_to_paths(paths, lem->paths[j]);
// 		j++;
// 	}
// }
//
// int			calc_max_output(t_lem *lem)
// {
// 	t_paths	*paths;
// 	size_t	len;
// 	size_t	i;
// 	int		max;
//
// 	len = lem->nb_paths;
// 	if (!(paths = (t_paths*)ft_memalloc(sizeof(*paths) * (len + 1))))
// 		return (-1);
// 	max = 0;
// 	i = 0;
// 	while (i < len)
// 	{
// 		ft_bzero(paths, sizeof(*paths) * (len));
// 		paths[0] = lem->paths[i];
// 		check_throughput(lem, paths, len);
// 		if (max < current_size(paths))
// 		{
// 			max = current_size(paths);
// 			ft_memdel((void**)&lem->solve);
// 			lem->solve = paths;
// 			lem->current_lines = lem->solve[max - 1][0] - 1;
// 			lem->current_bandwidth = compute_bandwidth(lem, lem->current_lines);
// 			lem->current_max_throughput = max;
// 			if (!(paths = (t_paths*)ft_memalloc(sizeof(*paths) * (len + 1))))
// 				return (-1);
// 		}
// 		i++;
// 	}
// 	free(paths);
// 	return (max);
// }
