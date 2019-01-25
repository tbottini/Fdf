#include "fdf.h"

int				wire_link(t_rmesh *wires, t_world_obj *cam, unsigned int *screen, t_vector2 cursor1, t_vector3 point, int fov)
{
	t_vector3	pos_point;
	t_vector2 	cursor;

	//verfier qu'on ne depasse pas

	if (point.x + 1 < wires->size_x)
	{
		vct3_value(&pos_point, point.x + 1, point.y, wires->wires[(int)point.y][(int)point.x + 1]);
		world_to_view(&cursor, *(cam->rotation), *(cam->position), pos_point, fov);
		trait(screen, cursor1, cursor, WHITE);
		wire_link(wires, cam, screen, cursor, pos_point,fov);
	}
	if (point.y + 1 < wires->size_y)
	{
		vct3_value(&pos_point, point.x, point.y + 1, wires->wires[(int)point.y + 1][(int)point.x]);
		world_to_view(&cursor, *(cam->rotation), *(cam->position), pos_point, fov);
		pixel_img(screen, cursor, BLUE);
		trait(screen, cursor1, cursor, WHITE);
		if (pos_point.x == 0)
			wire_link(wires, cam, screen, cursor, pos_point, fov);
	}
	return (0);
}

int 			start_point(t_rmesh *wires, t_world_obj *cam, unsigned int *screen, int fov)
{
	t_vector3	pos_point;
	t_vector2 	cursor;

	vct3_value(&pos_point, 0, 0, 0);
	vct3_value(&pos_point, 0, 0, wires->wires[(int)pos_point.y][(int)pos_point.x]);
	world_to_view(&cursor, *(cam->rotation), *(cam->position), pos_point, fov);
	pixel_img(screen, cursor, WHITE);
	wire_link(wires, cam, screen, cursor, pos_point, fov);
	//on recupere la position dans le monde qui est normalise
	//on la convertit en position sur ecran
	return (1);
}