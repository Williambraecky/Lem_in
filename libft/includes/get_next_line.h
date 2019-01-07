/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:48:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/18 15:11:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>

# define BUFF_SIZE 256

# define GNL_PRINT 1

typedef struct s_line	t_line;
struct		s_line
{
	int		fd;
	char	*str;
	size_t	size;
	size_t	remaining;
};

int			get_next_line(const int fd, char **line);
void		ft_clear_gnl(int fd);

#endif
