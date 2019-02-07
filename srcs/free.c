/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:53:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/07 17:13:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_rooms(t_lem *lem)
{
	size_t	i;

	if (!lem->rooms)
		return ;
	i = 0;
	while (i < lem->nb_rooms)
	{
		ft_strdel(&lem->rooms[i].name);
		ft_memdel((void**)&(lem->rooms[i].connections));
		ft_memdel((void**)&(lem->rooms[i].origin));
		i++;
	}
	ft_memdel((void**)&(lem->rooms));
}

static void	free_paths(t_lem *lem)
{
	size_t	i;

	if (!lem->paths)
		return ;
	i = 0;
	while (i < lem->nb_paths)
		ft_memdel((void**)&(lem->paths[i++]));
	ft_memdel((void**)&(lem->paths));
}

static void	free_dictionary(t_lem *lem)
{
	size_t	i;

	i = 0;
	while (i < lem->dict_len)
		ft_strdel(&lem->dictionary[i++]);
	ft_memdel((void**)&lem->dictionary);
}

void		free_lem(t_lem *lem)
{
	if (lem->fd)
		close(lem->fd);
	if (lem && lem->rooms)
		free_rooms(lem);
	if (lem && lem->hash_table)
		free(lem->hash_table);
	if (lem && lem->paths)
		free_paths(lem);
	if (lem && lem->dictionary)
		free_dictionary(lem);
	if (lem && lem->line)
		ft_strdel(&lem->line);
}
