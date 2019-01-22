/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/20 23:23:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** PROTOTYPE
*/

 int	move_ants_on_path(t_lem *lem, t_paths path, int force, size_t line)
{
	t_room	*current;
	t_room	*current2;
	size_t	i;
	int		ret;

	i = path[0];
	ret = 0;
	while (i-- > 1)
	{
		current = &lem->rooms[path[i + 1]];
		current2 = &lem->rooms[path[i]];
		if (current2->ant != 0 && current2->flag != LEM_START)
			move_ant(current2, current);
		else if (current2->flag == LEM_START &&
			current2->ant != lem->ant_count &&
			(force || (size_t)path[0] <= lem->current_lines - line + 1))
		{
			ret = 1;
			move_ant(current2, current);
		}
	}
	return (ret);
}

 void	move_ants(t_lem *lem)
{
	t_room	*end;
	t_room	*start;
	size_t	i;
	size_t	line;
	int		prev;

	if (!lem->paths)
		return ;
	end = &lem->rooms[lem->end];
	start = &lem->rooms[lem->start];
	line = 0;
	while (end->ant < lem->ant_count)
	{
		i = 0;
		while (i < lem->nb_paths)
		{
			prev = move_ants_on_path(lem, lem->paths[i],
			i == 0 || (prev && lem->paths[i - 1][0] == lem->paths[i][0]), line);
			i++;
		}
		line++;
		buffer_putchar('\n');
	}
	buffer_putnbr(line);
	buffer_putchar('\n');
}

int		main(int argc __attribute__((unused)), char **argv)
{
	t_lem	lem;
	size_t	i;

	(void)argv;
	if (argc != 1)
		error_exit(NULL);
	ft_memset(&lem, 0, sizeof(lem));
	lem.start = -1;
	lem.end = -1;
	parse_lemin(&lem);
	if (!lem_is_valid(&lem))
		error_exit(&lem);
	buffer_putchar('\n');
	lem.max_throughput = ft_min(lem.rooms[lem.start].nb_conn,
								lem.rooms[lem.end].nb_conn);
	buffer_flush();
	suurballe(&lem);
	sort_paths(lem.paths, lem.nb_paths);
	// lem.current_lines = lem.paths[lem.nb_paths - 1][0];
	lem.current_lines = 75;
	i = 0;
	while (lem.paths && lem.paths[i])
		print_path(&lem, lem.paths[i++]);
	ft_printf("NEEDED LINES %zu\n", calc_needed_lines(&lem));
	buffer_putchar('\n');
	// move_ants(&lem);
	free_lem(&lem);
	buffer_flush();
	return (0);
}
