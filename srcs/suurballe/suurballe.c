/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:17:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/07 17:20:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** TODO: Create duplicate of lem->paths
*/

static void	process_new_path(t_lem *lem, t_paths found)
{
	if (!is_path_clean(found))
		found = handle_conflict(lem, found, -1);
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

void		suurballe(t_lem *lem)
{
	t_paths	last;
	size_t	i;

	last = lem->algo(lem);
	if (!last)
		return ;
	lem_path_add(lem, last, NULL);
	prepare_map(lem);
	while (last && (!lem->max_paths || lem->nb_paths < (size_t)lem->max_paths))
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
