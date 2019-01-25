#include "fdf.h"

t_vector3		*vct3_new(int x, int y, int z)
{
	t_vector3	*new_vct3;

	if (!(new_vct3 = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	new_vct3->x = x;
	new_vct3->y = y;
	new_vct3->z = z;
	return (new_vct3);
}

t_vector3		*vct3_value(t_vector3 *vct, int x, int y, int z)
{
	vct->x = x;
	vct->y = y;
	vct->z = z;
	return (vct);
}

void			vct3_print(t_vector3 vct)
{
	ft_putstr("vector x : ");
	ft_putnbr(vct.x);
	ft_putstr(" y : ");
	ft_putnbr(vct.y);
	ft_putstr(" z : ");
	ft_putnbrcr(vct.z);
}

t_vector3		*vct3_add(t_vector3 *vct1, t_vector3 *vct2)
{
	vct1->x += vct2->x;
	vct1->y += vct2->y;
	vct1->z += vct2->z;
	return (vct1);
}

t_vector3		*vct3_cpy(t_vector3 *vct1, t_vector3 *vct2)
{
	vct1->x = vct2->x;
	vct1->y = vct2->y;
	vct1->z = vct2->z;
	return (vct1);
}

t_vector3		*vct3_mul(t_vector3 *vct1, int mul)
{
	vct1->x *= mul;
	vct1->y *= mul;
	vct1->z *= mul;
	return (vct1);
}

t_vector3		*vct3_negate(t_vector3 *vct)
{
	vct->x -= vct->x;
	vct->y -= vct->y;
	vct->z -= vct->z;
	return (vct);
}

int  sub(int a, int b)
{
	return (a - b);
}

int add(int a, int b)
{
	return (a + b);
}

int divi(int a, int b)
{
	return (a / b);
}

int mul(int a, int b)
{
	return (a * b);
}

t_vector3		*vct3_calc(t_vector3 *vct1, t_vector3 *vct2, int(*f)(int,int))
{
	vct1->x = f(vct1->x, vct2->x);
	vct1->y = f(vct1->y, vct2->y);
	vct1->z = f(vct1->z, vct2->z);
	return (vct1);
}