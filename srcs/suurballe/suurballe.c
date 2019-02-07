/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:17:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/07 13:40:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** TODO: Create duplicate of lem->paths
*/

static void	process_new_path(t_lem *lem, t_paths found)
{
	if (!is_path_clean(found))
	{
		found = handle_conflict(lem, found, -1);
	}
	lem_path_add(lem, found, NULL);
}

/*
** TODO: create stop condition ex -> path_finding.c should_continue
*/

void		suurballe(t_lem *lem)
{
	t_paths	last;

	last = lem->algo(lem);
	if (!last)
		return ;
	lem_path_add(lem, last, NULL);
	prepare_map(lem);
	while (last)
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
}
