/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:53:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/02 02:03:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_rooms(t_lem *lem)
{
	size_t	i;

	if (!lem->rooms)
		return ;
	i = 0;
	while (lem->rooms[i].name)
	{
		ft_strdel(&lem->rooms[i].name);
		ft_memdel((void**)&lem->rooms[i].connections);
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
	while (lem->paths[i])
		ft_memdel((void**)&(lem->paths[i++]));
	ft_memdel((void**)&(lem->paths));
}
