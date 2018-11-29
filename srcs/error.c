/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:51:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/29 15:18:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(t_lem *lem)
{
	ft_clear_gnl(0);
	ft_printf("ERROR\n");
	if (lem && lem->rooms)
		free_rooms(lem);
	if (lem && lem->paths)
		free_paths(lem);
	exit(0);
}
