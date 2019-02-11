/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:06:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/11 13:07:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	read_map(t_lem *lem, int *i, char **argv)
{
	(*i)++;
	if (!isatty(lem->fd) || lem->fd)
		error_message(lem, "Can only specify one map");
	if ((lem->fd = open(argv[*i], O_RDONLY)) == -1)
		error_message(lem, "Can not open file");
	(*i)++;
}

static void	read_max_paths(t_lem *lem, int *i, char **argv)
{
	(*i)++;
	if (!ft_strisnumber(argv[*i]))
		error_usage(lem);
	lem->max_paths = ft_atoi(argv[*i]);
	if (lem->max_paths <= 0)
		error_message(lem, "Invalid max number of paths");
	(*i)++;
}

static void	read_autonomy(t_lem *lem, int *i, char **argv)
{
	(*i)++;
	if (!ft_strisnumber(argv[*i]))
		error_usage(lem);
	lem->autonomy = ft_atoi(argv[*i]);
	if (lem->autonomy <= 0)
		error_message(lem, "Invalid autonomy");
	(*i)++;
}

void		read_lem_opt(t_lem *lem, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-a") && i + 1 < argc)
			read_autonomy(lem, &i, argv);
		else if (ft_strequ(argv[i], "-n") && i + 1 < argc)
			read_max_paths(lem, &i, argv);
		else if (ft_strequ(argv[i], "-m") && i + 1 < argc)
			read_map(lem, &i, argv);
		else if (ft_strequ(argv[i], "-s") && i++)
			lem->flags |= SHOW_FLAG;
		else if (ft_strequ(argv[i], "-h") && i++)
			lem->flags |= HIDE_FLAG;
		else if (ft_strequ(argv[i], "-r") && i++)
			lem->algo = reverse_bfs;
		else if (ft_strequ(argv[i], "-d") && i + 1 < argc)
			read_dictionary(lem, &i, argv);
		else
			error_usage(lem);
	}
}
