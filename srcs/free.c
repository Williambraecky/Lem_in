/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:53:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/20 18:24:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_rooms(t_lem *lem)
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

void	free_paths(t_lem *lem)
{
	size_t	i;

	if (!lem->paths)
		return ;
	i = 0;
	while (i < lem->nb_paths)
		ft_memdel((void**)&(lem->paths[i++]));
	ft_memdel((void**)&(lem->paths));
}

void	free_lem(t_lem *lem)
{
	if (lem && lem->rooms)
		free_rooms(lem);
	if (lem && lem->hash_table)
		free(lem->hash_table);
	// if (lem && lem->solve)
	// 	free(lem->solve);
	if (lem && lem->paths)
		free_paths(lem);
}
