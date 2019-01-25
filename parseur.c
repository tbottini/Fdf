#include "fdf.h"

int		ft_atoc(const char *str, int *i)
{
	int sign;
	int nbr;

	nbr = 0;
	sign = 1;
	while ((ft_isspace(str[*i]) || ft_isalpha(str[*i])) && str[*i] != '\n')
		*i = *i + 1;
	if (str[*i] == '\n')
	{
		(*i)++;
		return (-1);
	}
	if (str[*i] == '\0')
		return (-1);
	if (str[*i] == '-')
		sign = -1;
	while (str[*i] == '0')
		*i = *i + 1;
	if (str[*i] == '-' || str[*i] == '+')
		*i = *i + 1;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nbr = nbr * 10 + str[*i] - '0';
		*i = *i + 1;
	}
	return (nbr * sign);
}

int			fdf_check(t_rmesh *wires, char *str)
{
	int i;
	int count_elem;

	wires->size_x = 0;
	wires->size_y = 1;
	i = 0;
	while (ft_atoc(str, &i) != -1)
		wires->size_x++;
	while (str[i])
	{
		count_elem = 0;
		while (ft_atoc(str, &i) != -1)
			count_elem++;
		if (count_elem < wires->size_x)
			return (-1);
		wires->size_y++;
	}
	wires->size_x = wires->size_x;
	if (!(wires->wires = ft_new_cdt(wires->size_x, wires->size_y)))
	{
		free(wires);
		return (0);
	}
	return (1);
}

t_rmesh		*set_rmesh(t_rmesh *wires, char *str)
{
	int			i;
	int 		x;
	int			y;
	int			ret;

	y = -1;
	i = 0;
	while (++y != wires->size_y)
	{
		x = -1;
		while ((ret = ft_atoc(str, &i)) != -1)
			if (++x < wires->size_x)
				wires->wires[y][x] = ret;
	}
	return (wires);
}

void *ft_error_void(char *msg)
{
	ft_putendl(msg);
	return (NULL);
}

t_rmesh			*fdf_parseur(int ac, char **av)
{
	char 		*file;
	int 		fd;
	t_rmesh 	*wires;
	int			ret;

	if (ac != 2)
		return (ft_error_void("usage: fdf source_file"));
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		ft_putstr("fdf: ");
		ft_putstr(av[1]);\
		return (ft_error_void(": No such file or directory"));
	}
	if ((file = ft_get_file(fd)) == NULL
		|| !(wires = (t_rmesh *)malloc(sizeof(t_rmesh))))
		return (NULL);
	if ((ret = fdf_check(wires, file)) == -1)
	{
		free(file);
		return (ft_error_void("Invalid file"));
	}
	free(file);
	if (ret == 0 || set_rmesh(wires, file) == NULL)
		return (NULL);
	return (wires);
}
