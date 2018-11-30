/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 18:35:18 by wbraeckm         ###   ########.fr       */
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
	lem.max_throughput = ft_max(room_connlen(&lem.rooms[lem.start]),
								room_connlen(&lem.rooms[lem.end]));
	find_smallest_paths(&lem);
	i = 0;
	while (lem.paths && lem.paths[i])
		print_path(&lem, lem.paths[i++]);
	ft_printf("%d\n", calc_max_output(&lem));
	if (lem.rooms)
		free(lem.rooms);
	if (lem.paths)
		free(lem.paths);
	ft_printf("End\n");
	(void)argc;
	(void)argv;
	return (0);
}
