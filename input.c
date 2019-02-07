#include "fdf.h"

void 			input_deplacement(int key, t_mlx_data *fdf)
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
	if (key == KEY_W)
	{
		fdf->cam->position->y -= 5;
		fdf->cam->position->x -= 5;
	}
	else if (key == KEY_S)
	{
		fdf->cam->position->y += 5;
		fdf->cam->position->x += 5;
	}
	else if (key == KEY_A)
	{
		fdf->cam->position->y += 5;
		fdf->cam->position->x -= 5;
	}
	else if (key == KEY_D)
	{
		fdf->cam->position->y -= 5;
		fdf->cam->position->x += 5;
	}
}

void			close_window(t_mlx_data *fdf)
{
	rmesh_del(fdf->wires);
	free(fdf->cam->position);
	free(fdf->cam->rotation);
	free(fdf->cam);
	free(fdf->mouse_pos);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}


void			input_fov(int key, t_mlx_data *fdf)
{
	if (key == KEY_CTRL)
		fdf->cam->fov -= 4;
	else if (key == KEY_SHIFT)
		fdf->cam->fov += 4;
}

int				input_fdf(int key, t_mlx_data *fdf)
{
	if (key == KEY_ESC)
		close_window(fdf);
	if (key == KEY_W || key == KEY_A || key == KEY_D || key == KEY_S)
	{
		if (fdf->cam->proj == 1)
			input_deplacement(key, fdf);
		else
			input_movement_ortho(key, fdf);
	}
	else if (key == KEY_R)
		fdf->cam->position->y -= 4;
	else if (key == KEY_F)
		fdf->cam->position->y += 4;
	if (key == KEY_CTRL || key == KEY_SHIFT)
		input_fov(key, fdf);
	else if (key == KEY_P)
	{
		free(fdf->mouse_pos);
		fdf->mouse_pos = NULL;
		fdf->cam->proj = (fdf->cam->proj == 1) ? (2) : (1);
		ajust_cam(fdf);
	}
	ft_bzero(fdf->screen, fdf->cam->size_x * fdf->cam->size_y * 4);
	draw_wires(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_input(fdf);
	return (1);
}

int 			mouse_motion(int x, int y, t_mlx_data *fdf)
{
	t_vector2 tmp;

	if (fdf->cam->proj == 1)
	{
		if (fdf->mouse_pos == NULL)
		{
			if (!(fdf->mouse_pos = vct2_new(x / 2, y / 3)))
				return (-1);
			return (0);
		}
		vct2_value(&tmp, x / 2 - fdf->mouse_pos->x, y / 3 - fdf->mouse_pos->y);
		vct2_value(fdf->mouse_pos, x / 2, y / 3);
		fdf->cam->rotation->y -= tmp.x ;
		fdf->cam->rotation->x += tmp.y ;
		ft_bzero(fdf->screen, fdf->cam->size_x * fdf->cam->size_y * 4);
		draw_wires(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
		print_input(fdf);
	}
	return (0);
}