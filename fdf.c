/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:29:39 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 15:30:13 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int ac, char **av)
{
	t_mlx_data	*fdf;

	if (!(fdf = mlx_data_get("FDF", 90, ac, av)))
		return (0);
	camera_ajust(fdf);
	rmesh_draw(fdf);
	mlx_key_hook(fdf->win, &input_fdf, fdf);
	mlx_hook(fdf->win, MotionNotify, PointerMotionMask, &mouse_motion, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_input(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
