/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/03 20:23:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_lem	lem;
	size_t	i;

	if (argc != 1)
		error_exit(NULL);
	ft_memset(&lem, 0, sizeof(lem));
	parse_lemin(&lem);
	if (!lem_is_valid(&lem))
		error_exit(&lem);
	lem.max_throughput = ft_min(room_connlen(&lem.rooms[lem.start - 1]),
								room_connlen(&lem.rooms[lem.end - 1]));
	find_smallest_paths(&lem);
	i = 0;
	if (lem.rooms)
		free_rooms(&lem);
	if (lem.paths)
		free_paths(&lem);
	buffer_flush();
	(void)argc;
	(void)argv;
	return (0);
}
