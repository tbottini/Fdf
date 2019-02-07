#include "fdf.h"

t_vector3			*model_to_world(t_vector3 local_pos, t_vector3 trans, t_vector3 rot, int sca)
{
	t_vector3		*w_pos;
	t_vector3		*tmp;

	if (!(w_pos = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	if (!(tmp = (t_vector3 *)malloc(sizeof(t_vector3))))
	{
		free(w_pos);
		return (NULL);
	}
	vct3_cpy(w_pos, vct3_add(&local_pos, &trans));
	vct3_rotation(w_pos, rot);
	vct3_mul(w_pos, sca);
	return (w_pos);
}

t_vector2		*world_to_view(t_vector2 *cursor, t_camera cam, t_vector3 w_pos, float scale)
{
	t_vector3 delta;

	delta = *vct3_calc(&w_pos, cam.position, &sub);
	vct3_rotation(&delta, *cam.rotation);
	if (delta.z < 0)
	{
		vct2_value(cursor, -1, -1);
	}
	else if (cam.proj == 1)
	{
		cursor->x =	(delta.x * 1000 * scale / delta.z * tan(cam.fov / 2 * PI / 180));
		cursor->x += cam.size_x / 2;
		cursor->y = (delta.y * 1000 * scale / delta.z * tan(cam.fov / 2 * PI / 180));
		cursor->y += cam.size_y / 2;
		if (cursor->x < 0 || cursor->y < 0 || cursor->x > cam.size_x || cursor->y > cam.size_y)
			vct2_value(cursor, -1, -1);

	}
	else if (cam.proj == 2)
	{
		cursor->x =	delta.x * 10 * scale + cam.size_x / 2;
		cursor->y = delta.y * 10 * scale + cam.size_y / 2;
	}
	return (cursor);
}

t_vector3		*vct3_rotation(t_vector3 *pos, t_vector3 rot)
{

	t_vector3	tmp;

	rot.x = rot.x * PI / 180;
	rot.y = rot.y * PI / 180;
	rot.z = rot.z * PI / 180;
	vct3_cpy(&tmp, pos);
	pos->x = tmp.x * cos(rot.z) - tmp.y * sin(rot.z);
	pos->y = tmp.x * sin(rot.z) + tmp.y * cos(rot.z);
	vct3_cpy(&tmp, pos);
	pos->x = tmp.x * cos(rot.y) + tmp.z * sin(rot.y);
	pos->z = tmp.x * -sin(rot.y) + pos->z * cos(rot.y);
	vct3_cpy(&tmp, pos);
	pos->y = tmp.y * cos(rot.x) - tmp.z * sin(rot.x);
	pos->z = tmp.y * sin(rot.x) + tmp.z * cos(rot.x);
	return (pos);
}