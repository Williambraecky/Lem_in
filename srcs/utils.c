/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:43:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 18:08:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lem_is_valid(t_lem *lem)
{
	if (lem->start == 0 || lem->end == 0 || lem->ant_count <= 0)
		return (0);
	if (room_connlen(lem_get_room_id(lem, lem->start)) == 0)
		return (0);
	if (room_connlen(lem_get_room_id(lem, lem->end)) == 0)
		return (0);
	return (1);
}

void	del_path(void *elem, size_t content_size)
{
	(void)content_size;
	free(*(void**)elem);
	free(elem);
}

t_paths	path_dup(t_paths path)
{
	t_paths	new;
	size_t	len;

	len = path_len(path);
	if (!(new = ft_memalloc(sizeof(*new) * (len + 1))))
		return (NULL);
	while (len--)
		new[len] = path[len];
	return (new);
}

void	print_path(t_lem *lem, t_paths path)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = path_len(path);
	while (i < len)
	{
		ft_printf("%s", lem->rooms[path[i++] - 1].name);
		if (i < len)
			ft_printf("->");
	}
	ft_printf("\n");
}
