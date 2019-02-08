/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:34:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 15:50:51 by wbraeckm         ###   ########.fr       */
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

	i = path[0];
	ret = 0;
	while (i-- > 1)
	{
		current = &lem->rooms[path[i + 1]];
		current2 = &lem->rooms[path[i]];
		if (current2->ant != 0 && current2->flag != LEM_START)
			move_ant(lem, current2, current);
		else if (current2->flag == LEM_START &&
			current2->ant != lem->ant_count &&
			(force || (size_t)path[0] <= lem->current_lines - line + 1))
		{
			ret = 1;
			move_ant(lem, current2, current);
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

static void	show_info(t_lem *lem)
{
	size_t	i;

	if (!(lem->flags & SHOW_FLAG))
		return ;
	ft_printf("Number of paths: %zu\n", lem->nb_paths);
	ft_printf("Number of ants: %zu\n\n", lem->ant_count);
	i = 0;
	while (i < lem->nb_paths)
	{
		ft_printf("Path number: %zu (length=%d)\n", i + 1, lem->paths[i][0]);
		print_path(lem, lem->paths[i]);
		ft_putchar('\n');
		i++;
	}
	ft_printf("Needed lines: %zu\n",
		calc_needed_lines(lem, lem->paths, lem->nb_paths));
}

int			main(int argc, char **argv)
{
	t_lem	lem;

	(void)argv;
	ft_memset(&lem, 0, sizeof(lem));
	read_lem_opt(&lem, argc, argv);
	ft_printf("post options\n");
	if (!lem.algo)
		lem.algo = bfs;
	if (isatty(lem.fd))
	{
		error_message(&lem, "No map specified!");
		return (0);
	}
	lem.mode = argc == 1;
	lem.start = -1;
	lem.end = -1;
	parse_lemin(&lem);
	if (!lem_is_valid(&lem))
		error_exit(&lem);
	buffer_putchar('\n');
	buffer_flush();
	suurballe(&lem);
	sort_paths(lem.paths, lem.nb_paths);
	show_info(&lem);
	lem.current_lines = calc_needed_lines(&lem, lem.paths, lem.nb_paths);
	buffer_putchar('\n');
	if (!(lem.flags & HIDE_FLAG))
		move_ants(&lem);
	buffer_flush();
	free_lem(&lem);
	return (0);
}
