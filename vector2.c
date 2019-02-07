#include "fdf.h"

t_vector2		*vct2_new(int x, int y)
{
	t_vector2		*new_vector2;

	if (!(new_vector2 = (t_vector2 *)malloc(sizeof(t_vector2))))
		return (NULL);
	new_vector2->x = x;
	new_vector2->y = y;
	return (new_vector2);
}

t_vector2		*vct2_value(t_vector2 *vct, int x, int y)
{
	vct->x = x;
	vct->y = y;
	return (vct);
}

void			vct2_print(t_vector2 vct)
{
	ft_putstr("vector x : ");
	ft_putnbr(vct.x);
	ft_putstr(" y : ");
	ft_putnbrcr(vct.y);
}