/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:17:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 16:08:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	copy_paths(t_lem *lem)
{
	size_t	i;
	int		j;

	if (!(lem->copy = ft_memalloc(sizeof(*(lem->copy)) * lem->nb_paths)))
		error_exit(lem);
	lem->copy_len = lem->nb_paths;
	i = 0;
	while (i < lem->copy_len)
	{
		if (!(lem->copy[i] = ft_memalloc(sizeof(int) * (lem->paths[i][0] + 1))))
			error_exit(lem);
		lem->copy[i][0] = lem->paths[i][0];
		j = 1;
		while (j - 1 < lem->copy[i][0])
		{
			lem->copy[i][j] = lem->paths[i][j];
			j++;
		}
		i++;
	}
	sort_paths(lem->copy, lem->copy_len);
}

static void	process_new_path(t_lem *lem, t_paths found)
{
	size_t	i;

	copy_paths(lem);
	if (!is_path_clean(found))
		found = handle_conflict(lem, found);
	i = 0;
	while (i < lem->nb_paths)
	{
		if (!is_path_clean(lem->paths[i]))
		{
			lem->paths[i] = handle_conflict(lem, lem->paths[i]);
			i = 0;
		}
		else
			i++;
	}
	lem_path_add(lem, found, NULL);
}

static void	reverse_path(t_paths path)
{
	t_paths start;
	t_paths end;

	start = path + 1;
	end = path + path[0];
	while (start < end)
		ft_swapint(start++, end--);
}

/*
** TODO: create stop condition ex -> path_finding.c should_continue
*/

static int	should_continue(t_lem *lem)
{
	size_t	copy_lines;
	size_t	path_lines;

	if (lem->max_paths && lem->nb_paths >= (size_t)lem->max_paths)
		return (0);
	copy_lines = calc_needed_lines(lem, lem->copy, lem->copy_len);
	path_lines = calc_needed_lines(lem, lem->paths, lem->nb_paths);
	if (lem->copy && (copy_lines <= path_lines &&
		compute_bandwidth(lem->copy, lem->copy_len, copy_lines) ==
		compute_bandwidth(lem->paths, lem->nb_paths, path_lines)))
	{
		free_paths(lem);
		lem->paths = lem->copy;
		lem->copy = NULL;
		lem->nb_paths = lem->copy_len;
		return (0);
	}
	free_copy(lem);
	return (1);
}

void		suurballe(t_lem *lem)
{
	t_paths	last;
	size_t	i;

	last = lem->algo(lem);
	if (!last)
		return ;
	lem_path_add(lem, last, NULL);
	prepare_map(lem);
	while (last && should_continue(lem))
	{
		prepare_suurballe(lem);
		last = lem->algo(lem);
		if (last)
		{
			process_new_path(lem, last);
			reset_map(lem);
			sort_paths(lem->paths, lem->nb_paths);
		}
	}
	i = 0;
	while (lem->algo == reverse_bfs && i < lem->nb_paths)
		reverse_path(lem->paths[i++]);
}
