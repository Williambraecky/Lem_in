/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conflict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:05:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/20 18:20:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	find_conflict(t_lem *lem, t_paths path, int *index)
{
	int		i;
	size_t	j;

	i = 2;
	while (i < path[0])
	{
		j = 0;
		while (j < lem->nb_paths)
		{
			if (path != lem->paths[j] &&
				path_passes_through(lem->paths[j], path[i] & NO_FLAG))
			{
				*index = i;
				return (j);
			}
			j++;
		}
		i++;
	}
	return (lem->nb_paths);
}

static int		calc_conflict_end(t_paths path, t_paths conflict, int index)
{
	int	i;

	i = 1;
	while (i < conflict[0])
	{
		if (conflict[i] == path[index])
			break ;
		i++;
	}
	while (i > 0)
	{
		if ((path[index] & NO_FLAG) != (conflict[i] & NO_FLAG))
			break ;
		index++;
		i--;
	}
	return (index);
}

static t_paths	remove_conflict(t_lem *lem, t_paths *path,
	t_paths conflict, int index)
{
	t_paths	new;
	t_paths	new2;
	int		end;

	end = calc_conflict_end(*path, conflict, index);
	new = join_paths(lem, *path, conflict, path[0][index]);
	new2 = join_paths2(lem, conflict, path[0], path[0][end - 1] & NO_FLAG);
	// print_path(lem, new);
	// print_path(lem, new2);
	free(*path);
	*path = new;
	return (new2);
}

t_paths			handle_conflict(t_lem *lem, t_paths path)
{
	t_paths	new;
	size_t	conflict_path;
	int		index;

	// ft_printf("Trying to handle conflict for ");
	// print_path(lem, path);
	conflict_path = find_conflict(lem, path, &index);
	if (conflict_path == lem->nb_paths)
		return (path);
	new = remove_conflict(lem, &path, lem->paths[conflict_path], index);
	free(lem->paths[conflict_path]);
	lem->paths[conflict_path] = new;
	if (!is_path_clean(new))
		lem->paths[conflict_path] = handle_conflict(lem, new);
	return (path);
}
