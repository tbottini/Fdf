/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:26:17 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 17:13:55 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vct3		*vct3_calc(t_vct3 *vct1, t_vct3 *vct2, int (*f)(int, int))
{
	vct1->x = f(vct1->x, vct2->x);
	vct1->y = f(vct1->y, vct2->y);
	vct1->z = f(vct1->z, vct2->z);
	return (vct1);
}

int			sub(int a, int b)
{
	return (a - b);
}

int			add(int a, int b)
{
	return (a + b);
}

int			divi(int a, int b)
{
	return (a / b);
}

int			mul(int a, int b)
{
	return (a * b);
}
