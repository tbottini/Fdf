/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:30:27 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 16:53:41 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			pixel_img(t_mlx_data *fdf, t_vct2 vct, t_col color)
{
	if (vct.x < fdf->cam->x
		&& vct.y < fdf->cam->y
		&& vct.y > 0
		&& vct.x > 0)
		fdf->screen[vct.x + vct.y * fdf->cam->x] = color.c;
}

void			trait_id(t_mlx_data *fdf, t_vct2 vct1, t_vct2 vct2, t_col col)
{
	int			dx;
	int			dy;
	int			d;
	int			yi;

	dx = vct2.x - vct1.x;
	dy = vct2.y - vct1.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy + dx;
	while (vct1.x != vct2.x)
	{
		vct1.x++;
		pixel_img(fdf, vct1, col);
		if (d > 0)
		{
			vct1.y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
	}
}

void			trait_iu(t_mlx_data *fdf, t_vct2 vct1, t_vct2 vct2, t_col col)
{
	int			dx;
	int			dy;
	int			d;
	int			xi;

	dy = vct2.y - vct1.y;
	dx = vct2.x - vct1.x;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx + dy;
	while (vct1.y != vct2.y)
	{
		vct1.y++;
		pixel_img(fdf, vct1, col);
		if (d > 0)
		{
			vct1.x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
	}
}

void			trait(t_mlx_data *fdf, t_vct2 vct1, t_vct2 vct2, t_col col)
{
	if (vct2.x != -1 && vct2.y != -1
		&& vct1.x != -1 && vct1.y != -1)
	{
		if (abs(vct2.y - vct1.y) < abs(vct2.x - vct1.x))
		{
			if (vct1.x > vct2.x)
				trait_id(fdf, vct2, vct1, col);
			else
				trait_id(fdf, vct1, vct2, col);
		}
		else
		{
			if (vct1.y > vct2.y)
				trait_iu(fdf, vct2, vct1, col);
			else
				trait_iu(fdf, vct1, vct2, col);
		}
	}
}

void			print_input(t_mlx_data *fdf)
{
	char		s[30];

	ft_strcpy(s, "Esc Leave Fdf");
	mlx_string_put(fdf->mlx, fdf->win, 10, 10, WHITE, s);
	ft_strcpy(s, "W/A/S/d Move");
	mlx_string_put(fdf->mlx, fdf->win, 10, 30, WHITE, s);
	ft_strcpy(s, "Y/H U/J +/- Couleur");
	mlx_string_put(fdf->mlx, fdf->win, 10, 50, WHITE, s);
	if (fdf->cam->proj == 2)
	{
		ft_strcpy(s, "P Conique Proj");
		mlx_string_put(fdf->mlx, fdf->win, 10, 70, WHITE, s);
	}
	else
	{
		ft_strcpy(s, "R/F Up/down");
		mlx_string_put(fdf->mlx, fdf->win, 10, 70, WHITE, s);
		ft_strcpy(s, "P Iso Proj");
		mlx_string_put(fdf->mlx, fdf->win, 10, 90, WHITE, s);
		ft_strcpy(s, "Ctrl/Shift +/- FOV");
		mlx_string_put(fdf->mlx, fdf->win, 10, 110, WHITE, s);
		ft_strcpy(s, "Mouse Turn Cam");
		mlx_string_put(fdf->mlx, fdf->win, 10, 130, WHITE, s);
	}
}
