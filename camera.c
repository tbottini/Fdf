/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:24:21 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 17:02:15 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				wall_nb(int nb, int min, int max)
{
	if (nb > max)
		nb = max;
	else if (nb < min)
		nb = min;
	return (nb);
}

void			camera_ajust(t_mlx_data *fdf)
{
	if (fdf->cam->proj == 2)
	{
		vct3_value(fdf->cam->rotation, -45, 0, 45);
		vct3_value(fdf->cam->position, 636 + fdf->wires->x / 2,
								636 + fdf->wires->y / 2, -900);
	}
	else if (fdf->cam->proj == 1)
	{
		vct3_value(fdf->cam->rotation, 0, 0, 0);
		vct3_value(fdf->cam->position, fdf->wires->x / 2,
										fdf->wires->y / 2, -100);
	}
}

t_camera		*camera_new(int fov, int size_x, int size_y)
{
	t_camera	*camera;

	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	if (!(camera->position = (t_vct3 *)malloc(sizeof(t_vct3))))
		return (NULL);
	if (!(camera->rotation = (t_vct3 *)malloc(sizeof(t_vct3))))
		return (NULL);
	size_x = wall_nb(size_x, 450, 1920);
	size_y = wall_nb(size_y, 450, 1080);
	camera->x = size_x;
	camera->y = size_y;
	camera->fov = fov;
	camera->proj = 2;
	return (camera);
}

void			camera_del(t_camera *cam)
{
	free(cam->position);
	free(cam->rotation);
	free(cam);
}
