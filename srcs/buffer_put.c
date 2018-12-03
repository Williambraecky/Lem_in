/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 20:18:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/03 20:34:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	g_buffer[LEM_BUFFER_SIZE];
int		g_len = 0;

void	buffer_flush(void)
{
	write(1, g_buffer, g_len);
	g_len = 0;
}

void	buffer_putchar(char c)
{
	g_buffer[g_len++] = c;
	if (g_len == LEM_BUFFER_SIZE)
		buffer_flush();
}

void	buffer_putstr(char *str)
{
	if (!str)
		return ;
	while (*str)
		buffer_putchar(*str++);
}

void	buffer_putendl(char *str)
{
	buffer_putstr(str);
	buffer_putchar('\n');
}

/*
** Only works for positive ints
*/

void	buffer_putnbr(int i)
{
	if (i > 9)
		buffer_putnbr(i / 10);
	buffer_putchar(i % 10 + '0');
}
