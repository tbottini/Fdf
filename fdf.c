#include "fdf.h"


void			ajust_cam(t_mlx_data *fdf)
{
	vct3_value(fdf->cam->position, -3 * (fdf->wires->size_x), fdf->wires->size_y / 2, -3 * (fdf->wires->size_x));
	vct3_value(fdf->cam->rotation, 0,-47, 0);

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
	camera->size_x = size_x;
	camera->size_y = size_y;
	camera->fov = fov;
	camera->proj = 2;
	return (camera);
}

t_mlx_data		*mlx_data_get(char *screen_name, int fov, int ac, char **av)
{
	t_mlx_data	*ml;
	int 		bpp;
	int			endian;
	int 		width;

	if (!(ml = (t_mlx_data *)malloc(sizeof(t_mlx_data))))
		return (NULL);
	if (!(ml->wires = fdf_parseur(ac, av)) ||
		!(ml->cam = n_cam(fov, ml->wires->size_x * 50,
		ml->wires->size_y * 50)))
	{
		free(ml);
		return (NULL);
	}
	if (!(ml->mlx = mlx_init()) ||
		!(ml->win = mlx_new_window(ml->mlx, ml->cam->size_x, ml->cam->size_y, screen_name)) ||
		!(ml->img = mlx_new_image(ml, ml->cam->size_x, ml->cam->size_y)) ||
		!(ml->screen = (unsigned int *)mlx_get_data_addr(ml->img,
				&bpp, &width, &endian)))
		return (NULL);
	ml->mouse_pos = NULL;
	return (ml);
}



int 			main(int ac, char **av)
{
	t_mlx_data		*fdf;

	if (!(fdf = mlx_data_get("fdf", 75, ac, av)))
		return (0);
	ajust_cam(fdf);
	draw_wires(fdf);
	mlx_key_hook(fdf->win, &input_fdf, fdf);
	mlx_hook(fdf->win, MotionNotify, PointerMotionMask, &mouse_motion, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
	return (0);
}
