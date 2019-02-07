#include "fdf.h"

int				wire_link(t_mlx_data *fdf, t_vector2 cursor1, t_vector3 point, float scale)
{
	t_vector3	pos_point;
	t_vector2 	cursor;

	if (point.x + 1 < fdf->wires->size_x)
	{
		vct3_value(&pos_point, point.x + 1, point.y,
			fdf->scale_z * -fdf->wires->wires[(int)point.y][(int)point.x + 1] / 5);
		world_to_view(&cursor, *fdf->cam, pos_point, scale);
		trait(fdf, cursor1, cursor, fdf->color1);
		wire_link(fdf, cursor, pos_point, scale);
	}
	if (point.y + 1 < fdf->wires->size_y)
	{
		vct3_value(&pos_point, point.x, point.y + 1,
			fdf->scale_z * -fdf->wires->wires[(int)point.y + 1][(int)point.x] / 5);
		world_to_view(&cursor, *fdf->cam, pos_point, scale);
		trait(fdf, cursor1, cursor, fdf->color2);
		if (pos_point.x == 0)
			wire_link(fdf, cursor, pos_point, scale);
	}
	return (0);
}

int 			draw_wires(t_mlx_data *fdf)
{
	t_vector3	pos_point;
	t_vector2 	cursor;

	vct3_value(&pos_point, 0, 0, 0);
	vct3_value(&pos_point, 0, 0, fdf->scale_z * -fdf->wires->wires[0][0] / 5);
	world_to_view(&cursor, *fdf->cam, pos_point, fdf->wires->scale);
	wire_link(fdf, cursor, pos_point, fdf->wires->scale);
	vct3_value(&pos_point, -100, 0, -100);
	world_to_view(&cursor, *fdf->cam, pos_point, fdf->wires->scale);
	print_input(fdf);
	return (1);
}

void			rmesh_del(t_rmesh *rmesh)
{
	int i;

	i = 0;
	while (rmesh->wires[i])
	{
		free(rmesh->wires[i]);
		i++;
	}
	free(rmesh->wires);
	free(rmesh);
}