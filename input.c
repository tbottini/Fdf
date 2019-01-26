#include "fdf.h"

int				input_fdf(int key, t_mlx_data *fdf)
{
	float x_dir;
	float z_dir;

	z_dir = cos(fdf->cam->rotation->y * PI / 180) * 5;
	x_dir = sin(fdf->cam->rotation->y * PI / 180) * 5;
	printf("value ## %f %f\n", z_dir, x_dir);
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
	else if (key == KEY_Q)
		fdf->cam->rotation->y += 45;
	else if (key == KEY_E)
		fdf->cam->rotation->y -= 45;
	//altitude
	else if (key == KEY_R)
		fdf->cam->position->y++;
	else if (key == KEY_F)
		fdf->cam->position->y--;

	ft_bzero(fdf->screen, SCREEN_X * SCREEN_Y * 4);
	start_point(fdf->wires, fdf->cam, fdf->screen, 45);
	vct3_print(*fdf->cam->position);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	//start_point(wires, camera, fdf->screen, 45);
	return (1);
}

//deplacement devant soi
