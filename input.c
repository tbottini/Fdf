#include "fdf.h"

int				input_fdf(int key, t_mlx_data *fdf)
{
	float x_dir;
	float z_dir;

	z_dir = cos(fdf->cam->rotation->y * PI / 180) * 5;
	x_dir = sin(fdf->cam->rotation->y * PI / 180) * 5;
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
	else if (key == KEY_R)
		fdf->cam->position->y -= 4;
	else if (key == KEY_F)
		fdf->cam->position->y += 4;
	else if (key == KEY_CTRL)
		fdf->cam->fov -= 15;
	else if (key == KEY_SHIFT)
		fdf->cam->fov += 15;
	else if (key == KEY_Q)
	{
		vct3_value(fdf->cam->position, 50,50,-100);
		vct3_value(fdf->cam->rotation, 0,0,0);
	}
	else if (key == KEY_P)
		fdf->cam->proj = (fdf->cam->proj == 1) ? (2) : (1);
	ft_bzero(fdf->screen, fdf->cam->size_x * fdf->cam->size_y * 4);
	draw_wires(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (1);
}

int mouse_motion(int x, int y, t_mlx_data *fdf)
{
	t_vector2 tmp;

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
	vct3_print("cam rotation", *fdf->cam->rotation);
	return (0);
}