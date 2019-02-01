#include "fdf.h"

int				wire_link(t_mlx_data *fdf, t_vector2 cursor1, t_vector3 point, float scale)
{
	t_vector3	pos_point;
	t_vector2 	cursor;

	if (point.x + 1 < fdf->wires->size_x)
	{
		vct3_value(&pos_point, point.x + 1, point.y, -fdf->wires->wires[(int)point.y][(int)point.x + 1] / 5);
		world_to_view(&cursor, *fdf->cam, pos_point, scale);
		trait(fdf, cursor1, cursor, GREEN);
		wire_link(fdf, cursor, pos_point, scale);
	}
	if (point.y + 1 < fdf->wires->size_y)
	{
		vct3_value(&pos_point, point.x, point.y + 1, -fdf->wires->wires[(int)point.y + 1][(int)point.x] / 5);
		world_to_view(&cursor, *fdf->cam, pos_point, scale);
		trait(fdf, cursor1, cursor, GREEN);
		if (pos_point.x == 0)
			wire_link(fdf, cursor, pos_point, scale);
	}
	return (0);
}

int 		draw_floor(t_mlx_data *fdf, t_vector2 cursor1, t_vector3 point, float scale)
{
	t_vector2 cursor2;
	t_vector3 next_point;

	if (point.x <= 100)
	{
		vct3_value(&next_point, point.x + 1, fdf->wires->size_y - 1, point.z);
		world_to_view(&cursor2, *fdf->cam, point, scale);
		trait(fdf, cursor1, cursor2, WHITE);
		draw_floor(fdf, cursor2, next_point, scale);
	}
	if (point.z <= 100)
	{
		printf("passage\n");
		vct3_value(&next_point, point.x, fdf->wires->size_y - 1, point.z + 1);
		world_to_view(&cursor2, *fdf->cam, point, scale);
		trait(fdf, cursor1, cursor2, WHITE);
		if (point.x == -10)
			draw_floor(fdf, cursor2, next_point, scale);
	}
	return (1);
}

int 			draw_wires(t_mlx_data *fdf)
{
	t_vector3	pos_point;
	t_vector2 	cursor;
	float		scale;

	scale = 3.0;
	vct3_value(&pos_point, 0, 0, 0);
	vct3_value(&pos_point, 0, 0, -fdf->wires->wires[0][0] / 5);
	world_to_view(&cursor, *fdf->cam, pos_point, scale);
	pixel_img(fdf, cursor, WHITE);
	wire_link(fdf, cursor, pos_point, scale);
	vct3_value(&pos_point, -100, 0, -100);
	world_to_view(&cursor, *fdf->cam, pos_point, scale);
	//draw_floor(fdf, cursor, pos_point, scale);
	return (1);
}
