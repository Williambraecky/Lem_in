/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:27:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 16:42:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_hash_table(t_lem *lem)
{
	size_t	i;
	size_t	j;

	if (lem->nb_rooms == 0)
		error_exit(lem);
	if (!(lem->hash_table = ft_memalloc(sizeof(t_room*) *
	(lem->nb_rooms * 2))))
		error_exit(lem);
	i = 0;
	while (i < lem->nb_rooms)
	{
		j = lem->rooms[i].hash % (lem->nb_rooms * 2);
		while (lem->hash_table[j])
		{
			if (lem->hash_table[j]->hash == lem->rooms[i].hash &&
				ft_strequ(lem->hash_table[j]->name, lem->rooms[i].name))
				error_exit(lem);
			j++;
			if (j == (lem->nb_rooms * 2))
				j = 0;
		}
		lem->hash_table[j] = &lem->rooms[i++];
	}
}
