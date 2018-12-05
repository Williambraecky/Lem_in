/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:19:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/05 18:13:27 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	path_is_compatible(t_pathscombo *combo, t_paths path)
{
	size_t	i;

	i = 0;
	while (combo->paths[i])
	{
		if (path_collide(combo->paths[i], path))
			return (0);
		i++;
	}
	return (1);
}

void		del_combo(void *elem, size_t content_size)
{
	(void)content_size;
	free(((t_pathscombo*)elem)->paths);
	free(elem);
}

static void	add_to_combo(t_lem *lem, t_pathscombo *combo, t_paths path)
{
	t_pathscombo	new_combo;
	size_t			i;

	new_combo.nb_paths = combo->nb_paths + 1;
	if (!(new_combo.paths = ft_memalloc(sizeof(path) * (combo->nb_paths + 2))))
		error_exit(lem);
	i = 0;
	while (combo->paths[i])
	{
		new_combo.paths[i] = combo->paths[i];
		i++;
	}
	new_combo.paths[i] = path;
	if (new_combo.nb_paths > lem->current_max_throughput)
	{
		lem->current_max_throughput = new_combo.nb_paths;
		lem->current_combo = new_combo;
		ft_printf("TEST %zu\n", lem->current_combo.nb_paths);
	}
	ft_lstpushback(&lem->solutions, &new_combo, sizeof(new_combo));
}

void		add_to_combo_list(t_lem *lem, t_paths path)
{
	t_pathscombo	fresh_combo;
	t_pathscombo	*combo;
	t_list			*node;

	node = lem->solutions;
	while (node)
	{
		combo = (t_pathscombo*)node->content;
		if (path_is_compatible(combo, path))
		{
			add_to_combo(lem, combo, path);
			if (lem->current_max_throughput >= lem->max_throughput)
				return ;
		}
		node = node->next;
	}
	fresh_combo.nb_paths = 1;
	if (!(fresh_combo.paths = ft_memalloc(sizeof(path) * (2))))
		error_exit(lem);
	fresh_combo.paths[0] = path;
	ft_lstpushback(&lem->solutions, &fresh_combo, sizeof(fresh_combo));
	if (fresh_combo.nb_paths > lem->current_max_throughput)
	{
		lem->current_max_throughput = fresh_combo.nb_paths;
		lem->current_combo = fresh_combo;
	}
}
