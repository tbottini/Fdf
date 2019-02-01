
#include "fdf.h"

unsigned int 	color(unsigned char r, unsigned char g, unsigned char b)
{
    return (r * 256*256) + (g * 256) + b;
}

void			pixel_img(t_mlx_data *fdf, t_vector2 vct, unsigned int color)
{
	if (vct.x < fdf->cam->size_x && vct.y < fdf->cam->size_y && vct.y > 0
		&& vct.x > 0)
		fdf->screen[vct.x + vct.y * fdf->cam->size_x] = color;
}

static void			trait_img(t_mlx_data *fdf, t_vector2 vct1, t_vector2 vct2, unsigned int col)
{
	int dx;
	int dy;
	int D;
	int yi;

	dx = vct2.x - vct1.x;
	dy = vct2.y - vct1.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = 2 * dy + dx;
	while (vct1.x != vct2.x)
	{
		vct1.x++;
		pixel_img(fdf, vct1, col);
		if (D > 0)
		{
			vct1.y += yi;
			D -= 2*dx;
		}
		D += 2*dy;
	}
}

static void			trait_img_up(t_mlx_data *fdf, t_vector2 vct1, t_vector2 vct2, unsigned int col)
{
	int dx;
	int dy;
	int D;
	int xi;

	dy = vct2.y - vct1.y;
	dx = vct2.x - vct1.x;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2 * dx + dy;
	while (vct1.y != vct2.y)
	{
		vct1.y++;
		pixel_img(fdf, vct1, col);
		if (D > 0)
		{
			vct1.x += xi;
			D -= 2*dy;
		}
		D += 2*dx;
	}
}

void		trait(t_mlx_data *fdf, t_vector2 vct1, t_vector2 vct2, unsigned int col)
{
	if (abs(vct2.y - vct1.y) < abs(vct2.x - vct1.x))
	{
		if (vct1.x > vct2.x)
			trait_img(fdf, vct2, vct1, col);
		else
			trait_img(fdf, vct1, vct2, col);
	}
	else
	{
		if (vct1.y > vct2.y)
			trait_img_up(fdf, vct2, vct1, col);
		else
			trait_img_up(fdf, vct1, vct2, col);
	}

}