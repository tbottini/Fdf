/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:25:54 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 17:08:59 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				ft_atoc(char *str, int *i, int *nbr)
{
	int			sign;

	*nbr = 0;
	sign = 1;
	while (!ft_isdigit(str[*i]) && !(str[*i] == '-' && ft_isdigit(str[*i + 1]))
		&& str[*i] != '\n' && str[*i])
		*i = *i + 1;
	if (str[++(*i) - 1] == '\n')
		return (-1);
	(*i)--;
	if (str[*i] == '\0')
		return (-2);
	if (str[*i] == '-')
	{
		(*i)++;
		sign = -1;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*nbr = *nbr * 10 + str[*i] - '0';
		*i = *i + 1;
	}
	return (1);
}

int				pars(int fd, t_vct2 *len)
{
	int			nb;
	int			ret;
	char		*line;
	int			i;
	int			nb_elem_ligne;

	vct2_value(len, 0, 0);
	nb_elem_ligne = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = 0;
		while (ft_atoc(line, &i, &nb) > 0)
			nb_elem_ligne++;
		if (len->x == 0)
			len->x = nb_elem_ligne;
		else if (nb_elem_ligne < len->x)
			return (0);
		nb_elem_ligne = 0;
		free(line);
		len->y++;
	}
	free(line);
	close(fd);
	return ((ret == 0) ? 1 : -1);
}

t_rmesh			*rmesh_new(t_vct2 len)
{
	t_rmesh		*new_rmesh;

	if (!(new_rmesh = (t_rmesh *)malloc(sizeof(t_rmesh))))
		return (NULL);
	if (!(new_rmesh->wires = ft_new_cdt(len.x, len.y)))
	{
		free(new_rmesh);
		return (NULL);
	}
	return (new_rmesh);
}

t_rmesh			*get_rmesh(int fd, t_vct2 len)
{
	int			i;
	int			nb;
	t_rmesh		*wires;
	char		*line;

	if (!(wires = rmesh_new(len)))
		return (NULL);
	wires->y = -1;
	while (++(wires->y) < len.y)
	{
		i = 0;
		wires->x = -1;
		if (!(get_next_line(fd, &line)))
			return (NULL);
		while (++wires->x < len.x)
		{
			ft_atoc(line, &i, &nb);
			nb = wall_nb(nb, -128, 127);
			wires->wires[wires->y][wires->x] = nb;
		}
		free(line);
	}
	wires->x = len.x;
	close(fd);
	return (wires);
}

t_rmesh			*fdf_parseur(int ac, char **av)
{
	int			fd;
	t_rmesh		*wires;
	t_vct2		len;

	if (ac != 2)
	{
		return (ft_error_null("usage: fdf source_file"));
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		ft_putstr("fdf: ");
		ft_putstr(av[1]);
		return (ft_error_null(": No such file or directory"));
	}
	if (!pars(fd, &len))
	{
		return (ft_error_null("Invalid file"));
	}
	fd = open(av[1], O_RDONLY);
	if (!(wires = get_rmesh(fd, len)))
	{
		return (NULL);
	}
	return (wires);
}
