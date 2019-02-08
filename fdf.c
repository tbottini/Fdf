#include "fdf.h"

void			ajust_cam(t_mlx_data *fdf)
{
	if (fdf->cam->proj == 2)
	{
		vct3_value(fdf->cam->rotation, -45, 0, 45);
		vct3_value(fdf->cam->position, 636 + fdf->wires->size_x / 2,
								 636 + fdf->wires->size_y / 2, -900);
	}
	else if (fdf->cam->proj == 1)
	{
		vct3_value(fdf->cam->rotation, 0, 0, 0);
		vct3_value(fdf->cam->position, fdf->wires->size_x / 2, fdf->wires->size_y / 2, -100);
	}
}

t_camera		*n_cam(int fov, int size_x, int size_y)
{
	t_camera 	*camera;

	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	if (!(camera->position = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	if (!(camera->rotation = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	if (size_x > 1920)
		size_x = 1920;
	if (size_y > 1080)
		size_y = 1080;
	if (size_x < 450)
		size_x = 450;
	if (size_y < 450)
		size_y = 450;
	camera->size_x = size_x;
	camera->size_y = size_y;
	camera->fov = fov;
	camera->proj = 2;
	return (camera);
}

t_mlx_data		*mlx_data_connection(t_mlx_data *ml, char *name)
{
	int 		bpp;
	int			endian;
	int 		width;

	if (!(ml->mlx = mlx_init()))
		return (NULL);
	if (!(ml->win = mlx_new_window(ml->mlx, ml->cam->size_x, ml->cam->size_y, name)))
		return (NULL);
	if (!(ml->img = mlx_new_image(ml, ml->cam->size_x, ml->cam->size_y)))
		return (NULL);

	if (!(ml->screen = (unsigned int *)mlx_get_data_addr(ml->img,&bpp, &width, &endian)))
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
	if (!(ml->cam = n_cam(fov, (ml->wires->size_x + ml->wires->size_y) * 8.66 * 3,
		(ml->wires->size_x + ml->wires->size_y) * 15)))
		return (NULL);
	(void)screen_name;

	if ((ml->wires->size_x + ml->wires->size_y) * 15 > 1080)
		ml->wires->scale = 1080 / ((ml->wires->size_x + ml->wires->size_y) * 5.0);
	else if ((ml->wires->size_x + ml->wires->size_y) * 8.66 * 3 > 1920)
		ml->wires->scale = 1920 / ((ml->wires->size_x + ml->wires->size_y) * 8.66);
	else
		ml->wires->scale = 3;

	ml->mouse_pos = NULL;
	ml->scale_z = 1;
	color_stock_set(&ml->cs);

	if (!(mlx_data_connection(ml, screen_name)))
		return (NULL);
	return (ml);
}

void			print_input(t_mlx_data *fdf)
{
	char s[30];

	ft_strcpy(s, "Esc Leave Fdf");
	mlx_string_put(fdf->mlx, fdf->win, 10, 10, WHITE, s);
	ft_strcpy(s, "W/A/S/D Move");
	mlx_string_put(fdf->mlx, fdf->win, 10, 30, WHITE, s);
	if (fdf->cam->proj == 2)
	{
		ft_strcpy(s, "P Conique Proj");
		mlx_string_put(fdf->mlx, fdf->win, 10, 50, WHITE, s);
	}
	else
	{
		ft_strcpy(s, "R/F Up/Down");
		mlx_string_put(fdf->mlx, fdf->win, 10, 50, WHITE, s);
		ft_strcpy(s, "P Iso Proj");
		mlx_string_put(fdf->mlx, fdf->win, 10, 70, WHITE, s);
		ft_strcpy(s, "Ctrl/Shift +/- FOV");
		mlx_string_put(fdf->mlx, fdf->win, 10, 90, WHITE, s);
		ft_strcpy(s, "Mouse Turn Cam");
		mlx_string_put(fdf->mlx, fdf->win, 10, 110, WHITE, s);
	}
}

int 			main(int ac, char **av)
{
	t_mlx_data		*fdf;

	if (!(fdf = mlx_data_get("FDF", 90, ac, av)))
		return (0);
	ajust_cam(fdf);

	draw_wires(fdf);
	mlx_key_hook(fdf->win, &input_fdf, fdf);
	mlx_hook(fdf->win, MotionNotify, PointerMotionMask, &mouse_motion, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_input(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
