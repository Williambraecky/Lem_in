/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/07 18:46:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** PROTOTYPE
*/

// void	move_ants(t_lem *lem, t_paths path)
// {
// 	t_room	*end;
// 	t_room	*current;
// 	t_room	*current2;
// 	size_t	len;
//
// 	end = lem_get_room_id(lem, lem->end);
// 	while (end->ant != lem->ant_count)
// 	{
// 		len = path_len(path);
// 		while (len-- > 1)
// 		{
// 			current = lem_get_room_id(lem, path[len]);
// 			current2 = lem_get_room_id(lem, path[len - 1]);
// 			if ((current2->ant != 0 && current2->flag != LEM_START) ||
// 			(current2->flag == LEM_START && current2->ant != lem->ant_count))
// 				move_ant(current2, current);
// 		}
// 		buffer_putchar('\n');
// 	}
// }

static void	move_ants_on_path(t_lem *lem, t_paths path)
{
	t_room	*current;
	t_room	*current2;
	size_t	i;

	i = path_len(path);
	while (i-- > 2)
	{
		current2 = &lem->rooms[path[i + 1]];
		current = &lem->rooms[path[i]];
		if ((current2->ant != 0 && current2->flag != LEM_START) ||
		(current2->flag == LEM_START && current2->ant != lem->ant_count))
			move_ant(current2, current);
	}
}

static void	move_ants(t_lem *lem)
{
	t_room	*end;
	size_t	i;

	if (!lem->solve)
		return ;
	end = &lem->rooms[lem->end];
	while (end->ant != lem->ant_count)
	{
		i = 0;
		while (lem->solve[i])
		{
			if (i == 0 || path_len(lem->solve[i]) <= lem->ant_count)
				move_ants_on_path(lem, lem->solve[i]);
			i++;
		}
		buffer_putchar('\n');
	}
}

int		main(int argc __attribute__((unused)), char **argv)
{
	t_lem	lem;
	size_t	i;

	(void)argv;
	if (argc != 1)
		error_exit(NULL);
	ft_memset(&lem, 0, sizeof(lem));
	parse_lemin(&lem);
	if (!lem_is_valid(&lem))
		error_exit(&lem);
	buffer_putchar('\n');
	lem.max_throughput = ft_min(lem.rooms[lem.start - 1].nb_conn,
								lem.rooms[lem.end - 1].nb_conn);
	buffer_flush();
	find_smallest_paths(&lem);
	sort_paths(lem.paths, lem.nb_paths);
	// move_ants(&lem);
	i = 0;
	while (lem.paths && lem.solve && lem.solve[i])
		print_path(&lem, lem.solve[i++]);
	move_ants(&lem);
	free(lem.solve);
	if (lem.rooms)
		free_rooms(&lem);
	if (lem.solutions)
		ft_lstdel(&lem.solutions, del_combo);
	if (lem.paths)
		free_paths(&lem);
	buffer_flush();
	return (0);
}
