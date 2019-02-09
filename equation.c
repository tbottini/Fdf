/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:25:17 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 16:55:28 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vct3			*model_to_world(t_vct3 l_pos, t_vct3 tran, t_vct3 rot, int sca)
{
	t_vct3		*w_pos;
	t_vct3		*tmp;

	if (!(w_pos = (t_vct3 *)malloc(sizeof(t_vct3))))
		return (NULL);
	if (!(tmp = (t_vct3 *)malloc(sizeof(t_vct3))))
	{
		free(w_pos);
		return (NULL);
	}
	vct3_cpy(w_pos, vct3_calc(&l_pos, &tran, &add));
	vct3_rotation(w_pos, rot);
	vct3_mul(w_pos, sca);
	return (w_pos);
}

t_vct2			*world_to_view(t_vct2 *cur, t_camera cam, t_vct3 w_pos, float s)
{
	t_vct3		delta;

	delta = *vct3_calc(&w_pos, cam.position, &sub);
	vct3_rotation(&delta, *cam.rotation);
	if (delta.z < 0)
	{
		vct2_value(cur, -1, -1);
	}
	else if (cam.proj == 1)
	{
		cur->x = (delta.x * 1000 * s / delta.z * tan(cam.fov * PI / 360));
		cur->x += cam.x / 2;
		cur->y = (delta.y * 1000 * s / delta.z * tan(cam.fov * PI / 360));
		cur->y += cam.y / 2;
		if (cur->x < 0 || cur->y < 0 || cur->x > cam.x
			|| cur->y > cam.y)
			vct2_value(cur, -1, -1);
	}
	else if (cam.proj == 2)
	{
		cur->x = delta.x * 10 * s + cam.x / 2;
		cur->y = delta.y * 10 * s + cam.y / 2;
	}
	return (cur);
}

t_vct3			*vct3_rotation(t_vct3 *pos, t_vct3 rot)
{
	t_vct3		tmp;

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
