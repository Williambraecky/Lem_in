/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/05 18:11:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** PROTOTYPE
*/

void	move_ants(t_lem *lem, t_paths path)
{
	t_room	*end;
	t_room	*current;
	t_room	*current2;
	size_t	len;

	end = lem_get_room_id(lem, lem->end);
	while (end->ant != lem->ant_count)
	{
		len = path_len(path);
		while (len-- > 1)
		{
			current = lem_get_room_id(lem, path[len]);
			current2 = lem_get_room_id(lem, path[len - 1]);
			if ((current2->ant != 0 && current2->flag != LEM_START) ||
			(current2->flag == LEM_START && current2->ant != lem->ant_count))
				move_ant(current2, current);
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
	lem.max_throughput = ft_min(room_connlen(&lem.rooms[lem.start - 1]),
								room_connlen(&lem.rooms[lem.end - 1]));
	buffer_flush();
	find_smallest_paths(&lem);
	i = 0;
	ft_printf("%zu\n", ft_lstlen(lem.solutions));
	// while (lem.paths && lem.current_combo.paths[i])
	// 	print_path(&lem, lem.current_combo.paths[i++]);
	//move_ants(&lem, lem.paths[0]);
	if (lem.rooms)
		free_rooms(&lem);
	if (lem.solutions)
		ft_lstdel(&lem.solutions, del_combo);
	if (lem.paths)
		free_paths(&lem);
	buffer_flush();
	return (0);
}
