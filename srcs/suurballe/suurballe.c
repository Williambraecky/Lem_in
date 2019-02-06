/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:17:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/06 15:55:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static void	reset_map(t_lem *lem)
{
	t_room	*current;
	size_t	i;

	i = 0;
	while (i < lem->nb_rooms)
	{
		current = &lem->rooms[i];
		ft_memcpy(current->connections, current->origin,
			sizeof(*(current->origin)) * (current->origin_conn));
		current->nb_conn = current->origin_conn;
		current->used = 0;
		current->reverse = -1;
		i++;
	}
}

static void	prepare_suurballe(t_lem *lem)
{
	size_t	i;
	int		j;

	if (!lem->paths)
		return ;
	i = 0;
	while (i < lem->nb_paths)
	{
		j = 1;
		while (j < lem->paths[i][0])
		{
			room_del_connections(&lem->rooms[lem->paths[i][j]],
			lem->paths[i][j + 1]);
			lem->rooms[lem->paths[i][j + 1]].reverse = lem->paths[i][j];
			j++;
		}
		i++;
	}
}

/*
** TODO: path linking
*/

static void	process_new_path(t_lem *lem, t_paths found)
{
	if (!is_path_clean(found))
	{
		found = handle_conflict(lem, found, -1);
	}
	lem_path_add(lem, found, NULL);
}

static void	stuff(t_lem *lem)
{
	size_t	i;

	i = 0;
	ft_printf("Nb paths; %zu\n", lem->nb_paths);
	while (i < lem->nb_paths)
	{
		if (!is_path_clean(lem->paths[i]))
			ft_printf("unclean path in solution\n");
		// ft_printf("%zu length : %d\n", i, lem->paths[i][0]);
		// print_path(lem, lem->paths[i]);
		i++;
	}
}

/*
** TODO: create stop condition ex -> path_finding.c should_continue
*/

void		suurballe(t_lem *lem)
{
	t_paths	last;

	if (lem->mode)
		last = bfs(lem);
	else
		last = reverse_bfs(lem);
	if (!last)
		return ;
	lem_path_add(lem, last, NULL);
	ft_printf("NEEDED LINES %zu\n", calc_needed_lines(lem));
	stuff(lem);
	prepare_map(lem);
	// print_path(lem, last);
	while (last)
	{
		prepare_suurballe(lem);
		if (lem->mode)
			last = bfs(lem);
		else
			last = reverse_bfs(lem);
		if (last)
		{
			// ft_printf("\n\nnew\n");
			// print_path(lem, last);
			process_new_path(lem, last);
			reset_map(lem);
			sort_paths(lem->paths, lem->nb_paths);
			ft_printf("NEEDED LINES %zu\n", calc_needed_lines(lem));
			stuff(lem);
		}
	}
	reset_map(lem);
	ft_putstr("end suurballe\n");
}
