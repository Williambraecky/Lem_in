/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:51:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/11 13:45:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_usage(t_lem *lem)
{
	ft_printf("Usage: ./lem-in [-a number -n number \
-m map -v -s -d dictionary -r]\n");
	if (lem->fd)
		close(lem->fd);
	free_lem(lem);
	exit(0);
}

void	error_message(t_lem *lem, char *msg)
{
	buffer_flush();
	ft_printf("\nERROR: %s\n", msg);
	free_lem(lem);
	exit(0);
}

void	error_exit(t_lem *lem)
{
	if (!isatty(lem->fd))
		ft_clear_gnl(lem->fd);
	buffer_flush();
	ft_printf("\nERROR\n");
	free_lem(lem);
	exit(0);
}
