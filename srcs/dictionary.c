/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:44:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/07 17:45:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ensure_enough_space(t_lem *lem, int fd)
{
	char	**new;
	size_t	new_size;

	if (lem->dict_len < lem->max_dict_len)
		return ;
	if (lem->max_dict_len == 0)
		new_size = DICT_LEN_START;
	else
		new_size = lem->max_dict_len * 2;
	if (!(new = ft_realloc(lem->dictionary,
		lem->dict_len * sizeof(char *), new_size * sizeof(char *))))
	{
		close(fd);
		error_exit(lem);
	}
	lem->max_dict_len = new_size;
	lem->dictionary = new;
}

void		read_dictionary(t_lem *lem, int *i, char **argv)
{
	int		fd;
	int		ret;

	(*i)++;
	if ((fd = open(argv[*i], O_RDONLY)) == -1)
		error_message(lem, "Could not open file");
	ft_printf("Dictionary \"%s\":\n", argv[*i]);
	while ((ret = get_next_line(fd, &lem->line)))
	{
		ensure_enough_space(lem, fd);
		lem->dictionary[lem->dict_len++] = lem->line;
		lem->line = NULL;
	}
	if (ret == -1)
	{
		close(fd);
		error_message(lem, "Error reading file");
	}
	close(fd);
	ft_putchar('\n');
	(*i)++;
}
