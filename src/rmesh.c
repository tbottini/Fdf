/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmesh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:26:03 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 17:11:48 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				wire_link(t_mlx_data *fdf, t_vct2 cursor1, t_vct3 pt, float s)
{
	t_vct3		pos_point;
	t_vct2		cursor;

	if (pt.x + 1 < fdf->wires->x)
	{
		vct3_value(&pos_point, pt.x + 1, pt.y,
			fdf->scale_z * -fdf->wires->wires[(int)pt.y][(int)pt.x + 1] / 5);
		world_to_view(&cursor, *fdf->cam, pos_point, s);
		trait(fdf, cursor1, cursor, cs_color(fdf->cs, 1));
		wire_link(fdf, cursor, pos_point, s);
	}
	if (pt.y + 1 < fdf->wires->y)
	{
		vct3_value(&pos_point, pt.x, pt.y + 1,
			fdf->scale_z * -fdf->wires->wires[(int)pt.y + 1][(int)pt.x] / 5);
		world_to_view(&cursor, *fdf->cam, pos_point, s);
		trait(fdf, cursor1, cursor, cs_color(fdf->cs, 2));
		if (pos_point.x == 0)
			wire_link(fdf, cursor, pos_point, s);
	}
	return (0);
}

int				rmesh_draw(t_mlx_data *fdf)
{
	t_vct3		pos_point;
	t_vct2		cursor;

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
	int			i;

	i = 0;
	while (rmesh->wires[i])
	{
		free(rmesh->wires[i]);
		i++;
	}
	free(rmesh->wires);
	free(rmesh);
}
