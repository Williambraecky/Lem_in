/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:51:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/05 17:46:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(t_lem *lem)
{
	ft_clear_gnl(0);
	buffer_flush();
	ft_printf("ERROR\n");
	if (lem && lem->rooms)
		free_rooms(lem);
	if (lem && lem->solutions)
		ft_lstdel(&lem->solutions, del_combo);
	if (lem && lem->paths)
		free_paths(lem);
	exit(0);
}
