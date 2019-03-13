/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:25:48 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 16:56:50 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx_data		*mlx_data_connection(t_mlx_data *ml, char *name)
{
	int			b;
	int			e;
	int			w;

	if (!(ml->mlx = mlx_init()))
		return (NULL);
	if (!(ml->win = mlx_new_window(ml->mlx, ml->cam->x, ml->cam->y, name)))
		return (NULL);
	if (!(ml->img = mlx_new_image(ml, ml->cam->x, ml->cam->y)))
		return (NULL);
	ml->screen = (unsigned int *)mlx_get_data_addr(ml->img, &b, &w, &e);
	if (!ml)
		return (NULL);
	return (ml);
}

t_mlx_data		*mlx_data_get(char *screen_name, int fov, int ac, char **av)
{
	t_mlx_data	*ml;

	if (!(ml = (t_mlx_data *)malloc(sizeof(t_mlx_data))))
		return (NULL);
	if (!(ml->wires = fdf_parseur(ac, av)))
		return (NULL);
	if (!(ml->cam = camera_new(fov, (ml->wires->x + ml->wires->y) * 8.66 * 3,
		(ml->wires->x + ml->wires->y) * 15)))
		return (NULL);
	(void)screen_name;
	if ((ml->wires->x + ml->wires->y) * 15 > 1080)
		ml->wires->scale = 1080 / ((ml->wires->x + ml->wires->y) * 5.0);
	else if ((ml->wires->x + ml->wires->y) * 8.66 * 3 > 1920)
		ml->wires->scale = 1920 / ((ml->wires->x + ml->wires->y) * 8.66);
	else
		ml->wires->scale = 3;
	ml->mouse_pos = NULL;
	ml->scale_z = 1;
	color_stock_set(&ml->cs);
	if (!(mlx_data_connection(ml, screen_name)))
		return (NULL);
	return (ml);
}

void			mlx_data_close(t_mlx_data *fdf)
{
	rmesh_del(fdf->wires);
	camera_del(fdf->cam);
	if (fdf->mouse_pos)
		free(fdf->mouse_pos);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->mlx);
	free(fdf);
	exit(0);
}

void			fdf_refresh(t_mlx_data *fdf)
{
	ft_bzero(fdf->screen, fdf->cam->x * fdf->cam->y * 4);
	rmesh_draw(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_input(fdf);
}
