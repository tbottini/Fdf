/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:25:41 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 16:44:21 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			input_deplacement(int key, t_mlx_data *fdf)
{
	float x_dir;
	float z_dir;

	z_dir = cos(fdf->cam->rotation->y * PI / 180) * 15;
	x_dir = sin(fdf->cam->rotation->y * PI / 180) * 15;
	if (key == KEY_W)
	{
		fdf->cam->position->z += z_dir;
		fdf->cam->position->x -= x_dir;
	}
	else if (key == KEY_A)
	{
		fdf->cam->position->z -= x_dir;
		fdf->cam->position->x -= z_dir;
	}
	else if (key == KEY_S)
	{
		fdf->cam->position->z -= z_dir;
		fdf->cam->position->x += x_dir;
	}
	else if (key == KEY_D)
	{
		fdf->cam->position->z += x_dir;
		fdf->cam->position->x += z_dir;
	}
}

void			input_movement_ortho(int key, t_mlx_data *fdf)
{
	fdf->cam->position->y += (key == KEY_S || key == KEY_A) ? 5 : -5;
	fdf->cam->position->x += (key == KEY_S || key == KEY_D) ? 5 : -5;
}

void			switch_projection(t_mlx_data *fdf)
{
	free(fdf->mouse_pos);
	fdf->mouse_pos = NULL;
	fdf->cam->proj = (fdf->cam->proj == 1) ? (2) : (1);
	camera_ajust(fdf);
}

int				input_fdf(int key, t_mlx_data *fdf)
{
	if (key == KEY_W || key == KEY_A || key == KEY_D || key == KEY_S)
	{
		if (fdf->cam->proj == 1)
			input_deplacement(key, fdf);
		else
			input_movement_ortho(key, fdf);
	}
	else if (key == KEY_P)
		switch_projection(fdf);
	else if (key == KEY_R || key == KEY_F)
		fdf->cam->position->y += (key == KEY_F) ? 15 : -15;
	else if (key == KEY_T || key == KEY_G)
		fdf->scale_z += (key == KEY_T) ? 1 : -1;
	else if (key == KEY_CTRL || key == KEY_SHIFT)
		fdf->cam->fov += (key == KEY_SHIFT) ? 4 : -4;
	else if (key == KEY_U || key == KEY_J || key == KEY_H || key == KEY_Y)
		input_color(&fdf->cs, key);
	fdf_refresh(fdf);
	if (key == KEY_ESC)
		mlx_data_close(fdf);
	return (1);
}

int				mouse_motion(int x, int y, t_mlx_data *fdf)
{
	t_vct2 tmp;

	if (fdf->mouse_pos == NULL)
	{
		if (!(fdf->mouse_pos = vct2_new(x / 2, y / 3)))
			return (-1);
		return (0);
	}
	vct2_value(&tmp, x / 2 - fdf->mouse_pos->x, y / 3 - fdf->mouse_pos->y);
	vct2_value(fdf->mouse_pos, x / 2, y / 3);
	if (fdf->cam->proj == 1)
	{
		fdf->cam->rotation->y -= tmp.x;
		fdf->cam->rotation->x += tmp.y;
		fdf_refresh(fdf);
	}
	return (0);
}
