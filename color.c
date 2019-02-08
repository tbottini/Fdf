#include "fdf.h"

void		color_stock_set(t_color_stock *cs)
{
	cs->color1 = WHITE;
	cs->color2 = WHITE;
	cs->color_s1 = 0;
	cs->color_s2 = 0;
	cs->color_stock[0] = WHITE;
	cs->color_stock[1] = RED;
	cs->color_stock[2] = PURPLE;
	cs->color_stock[3] = BLUE;
	cs->color_stock[4] = CYAN;
	cs->color_stock[5] = GREEN;
	cs->color_stock[6] = YELLOW;
	cs->color_stock[7] = PCHARRIE;
	cs->color_stock[8] = FRATARDI;
	cs->color_stock[9] = BEIGE;
	cs->color_stock[10] = BLACK;
}

int 		input_color(t_color_stock *cs, int key)
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

int 		cs_color(t_color_stock cs, char color)
{
	if (color == 1)
		return (cs.color_stock[cs.color_s1]);
	else
		return (cs.color_stock[cs.color_s2]);
}