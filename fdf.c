
#include "fdf.h"

void 			band(unsigned int *screen, int pos, int size, int color)
{
	int end;
	int i;

	i = -1;
	end = size * SCREEN_X;
	while (++i != end)
		screen[i + (pos * SCREEN_X)] = color;
}

t_world_obj		*new_world_obj()
{
	t_world_obj 	*camera;

	if (!(camera = (t_world_obj *)malloc(sizeof(t_world_obj))))
		return (NULL);
	if (!(camera->position = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	if (!(camera->rotation = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	return (camera);
}

t_mlx_data		*mlx_data_get(char *screen_name)
{
	t_mlx_data *ml;
	int bpp;
	int endian;
	int width;

	if (!(ml = (t_mlx_data *)malloc(sizeof(t_mlx_data))))
		return (NULL);
	ml->mlx = mlx_init();
	ml->win = mlx_new_window(ml->mlx, SCREEN_X, SCREEN_Y, screen_name);
	ml->img = mlx_new_image(ml, SCREEN_X, SCREEN_Y);
	ml->screen = (unsigned int *)mlx_get_data_addr(ml->img,
				&bpp, &width, &endian);

	return (ml);
}

int 			main(int ac, char **av)
{
	t_mlx_data		*fdf;
	t_vector3 pt;

	fdf = mlx_data_get("fdf");
	if (!(fdf->wires = fdf_parseur(ac, av)))
		return (0);
	if (!(fdf->cam = new_world_obj()))
		return (0);
	ft_print_dtc_nb(fdf->wires->wires, fdf->wires->size_x);
	vct3_value(fdf->cam->position, 0, 0, -10);
	vct3_value(fdf->cam->rotation, 0, 0,0);
	//affichage
	start_point(fdf->wires, fdf->cam, fdf->screen, 45);

	pt.x = 0;
	pt.y = 0;
	pt.z = 0;
	//headers bot
	//band(fdf->screen, 0, 100, color(100, 0, 0));
	//band(fdf->screen, SCREEN_Y - 100, 100, color(100, 0, 0));
	//input
	mlx_key_hook(fdf->win, &input_fdf, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
	return (0);
}
