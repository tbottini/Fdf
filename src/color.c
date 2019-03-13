/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:24:54 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 16:29:06 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	rgb_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r * 256 * 256) + (g * 256) + b;
}

void			color_stock_set(t_color_stock *cs)
{
	cs->color1.c = WHITE;
	cs->color2.c = WHITE;
	cs->color_s1 = 0;
	cs->color_s2 = 0;
	cs->color_stock[0].c = WHITE;
	cs->color_stock[1].c = RED;
	cs->color_stock[2].c = PURPLE;
	cs->color_stock[3].c = BLUE;
	cs->color_stock[4].c = CYAN;
	cs->color_stock[5].c = GREEN;
	cs->color_stock[6].c = YELLOW;
	cs->color_stock[7].c = PCHARRIE;
	cs->color_stock[8].c = FRATARDI;
	cs->color_stock[9].c = BEIGE;
	cs->color_stock[10].c = BLACK;
}

int				input_color(t_color_stock *cs, int key)
{
	if (key == KEY_Y)
		cs->color_s1++;
	if (key == KEY_H)
		cs->color_s1--;
	if (key == KEY_U)
		cs->color_s2++;
	if (key == KEY_J)
		cs->color_s2--;
	if (cs->color_s1 > 10)
		cs->color_s1 = 0;
	if (cs->color_s1 < 0)
		cs->color_s1 = 10;
	if (cs->color_s2 > 10)
		cs->color_s2 = 0;
	if (cs->color_s2 < 0)
		cs->color_s2 = 10;
	return (1);
}

t_col			cs_color(t_color_stock cs, char color)
{
	if (color == 1)
		return (cs.color_stock[cs.color_s1]);
	else
		return (cs.color_stock[cs.color_s2]);
}
