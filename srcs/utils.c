/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:43:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/29 16:45:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lem_is_valid(t_lem *lem)
{
	if (lem->start == 0 || lem->end == 0 || lem->ant_count == 0)
		return (0);
	if (room_connlen(lem_get_room_id(lem, lem->start)) == 0)
		return (0);
	if (room_connlen(lem_get_room_id(lem, lem->end)) == 0)
		return (0);
	return (1);
}
