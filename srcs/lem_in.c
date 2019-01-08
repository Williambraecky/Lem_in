/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/08 15:18:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** PROTOTYPE
*/

static int	move_ants_on_path(t_lem *lem, t_paths path, int force, size_t line)
{
	t_room	*current;
	t_room	*current2;
	size_t	i;
	int		ret;

	i = path_len(path);
	ret = 0;
	while (i-- > 1)
	{
		current = &lem->rooms[path[i + 1] - 1];
		current2 = &lem->rooms[path[i] - 1];
		if (current2->ant != 0 && current2->flag != LEM_START)
			move_ant(current2, current);
		else if (current2->flag == LEM_START &&
			current2->ant != lem->ant_count &&
			(force || path_len(path) <= lem->current_lines - line + 1))
		{
			ret = 1;
			move_ant(current2, current);
		}
	}
	return (ret);
}

static void	move_ants(t_lem *lem)
{
	t_room	*end;
	t_room	*start;
	size_t	i;
	size_t	line;
	int		prev;

	if (!lem->solve)
		return ;
	end = &lem->rooms[lem->end - 1];
	start = &lem->rooms[lem->start - 1];
	line = 0;
	while (end->ant < lem->ant_count)
	{
		i = 0;
		while (lem->solve[i])
		{
			prev = move_ants_on_path(lem, lem->solve[i],
			i == 0 || (prev && lem->solve[i - 1][0] == lem->solve[i][0]), line);
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
	parse_lemin(&lem);
	if (!lem_is_valid(&lem))
		error_exit(&lem);
	buffer_putchar('\n');
	lem.max_throughput = ft_min(lem.rooms[lem.start - 1].nb_conn,
								lem.rooms[lem.end - 1].nb_conn);
	buffer_flush();
	find_smallest_paths(&lem);
	sort_paths(lem.solve, lem.current_max_throughput);
	// move_ants(&lem);
	i = 0;
	while (lem.paths && lem.solve && lem.solve[i])
		print_path(&lem, lem.solve[i++]);
	ft_putchar('\n');
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
