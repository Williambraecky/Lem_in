/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/03 21:19:18 by wbraeckm         ###   ########.fr       */
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
// 				(current2->flag == LEM_START && current2->ant != lem->ant_count))
// 				move_ant(current2, current);
// 		}
// 		buffer_putchar('\n');
// 	}
// }

int		main(int argc, char **argv)
{
	t_lem	lem;

	if (argc != 1)
		error_exit(NULL);
	ft_memset(&lem, 0, sizeof(lem));
	parse_lemin(&lem);
	if (!lem_is_valid(&lem))
		error_exit(&lem);
	buffer_putchar('\n');
	lem.max_throughput = ft_min(room_connlen(&lem.rooms[lem.start - 1]),
								room_connlen(&lem.rooms[lem.end - 1]));
	buffer_flush();
	find_smallest_paths(&lem);
	move_ants(&lem, lem.paths[0]);
	if (lem.rooms)
		free_rooms(&lem);
	if (lem.paths)
		free_paths(&lem);
	buffer_flush();
	(void)argc;
	(void)argv;
	return (0);
}
