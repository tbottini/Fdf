#include "fdf.h"

int			ft_atoc(char *str, int *i, int *nbr)
{
	int sign;

	*nbr = 0;
	sign = 1;
	while (!ft_isdigit(str[*i]) && !(ft_isdigit(str[*i + 1]) && str[*i] == '-')
		&& str[*i] != '\n' && str[*i])
		*i = *i + 1;
	if (str[*i] == '\n')
	{
		(*i)++;
		return (-1);
	}
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

int 		pars(int fd, t_vector2 *len)
{
	int 	nb;
	int 	ret;
	char 	*line;
	int 	i;
	int 	nb_elem_ligne;

	len->x = 0;
	len->y = 0;
	i = 0;
	nb_elem_ligne = 0;
	ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		while (ft_atoc(line, &i, &nb) > 0)
			nb_elem_ligne++;
		if (len->x == 0)
			len->x = nb_elem_ligne;
		else if (nb_elem_ligne < len->x)
			return (0);
		nb_elem_ligne = 0;
		free(line);
		len->y++;
		i = 0;
	}
	if (ret == -1)
		return (0);
	close (fd);
	return (1);
}

t_rmesh		*rmesh_new(t_vector2 len)
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

t_rmesh		*get_rmesh(int fd, t_vector2 len)
{
	int			i;
	int			nb;
	t_rmesh		*wires;
	char		*line;

	if (!(wires = rmesh_new(len)))
		return (NULL);
	wires->size_y = -1;
	while (++(wires->size_y) < len.y)
	{
		i = 0;
		wires->size_x = -1;
		if (!(get_next_line(fd, &line)))
			return (NULL);
		while (++wires->size_x < len.x)
		{
			ft_atoc(line, &i, &nb);
			if (nb > 127)
				nb = 127;
			else if (nb < -128)
				nb = -128;
			wires->wires[wires->size_y][wires->size_x] = nb;
		}
		free(line);
	}
	wires->size_x = len.x;
	return (wires);
}

t_rmesh			*fdf_parseur(int ac, char **av)
{
	int 		fd;
	t_rmesh 	*wires;
	t_vector2	len;

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
