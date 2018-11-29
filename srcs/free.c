/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:53:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/29 17:27:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_rooms(t_lem *lem)
{
	if (!lem->rooms)
		return ;
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
