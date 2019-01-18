/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:51:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/18 14:32:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(t_lem *lem)
{
	ft_clear_gnl(0);
	buffer_flush();
	ft_printf("ERROR\n");
	free_lem(lem);
	exit(0);
}
