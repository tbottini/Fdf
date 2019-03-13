/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:26:08 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 17:12:26 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vct2		*vct2_new(int x, int y)
{
	t_vct2	*new_vector2;

	if (!(new_vector2 = (t_vct2 *)malloc(sizeof(t_vct2))))
		return (NULL);
	new_vector2->x = x;
	new_vector2->y = y;
	return (new_vector2);
}

t_vct2		*vct2_value(t_vct2 *vct, int x, int y)
{
	vct->x = x;
	vct->y = y;
	return (vct);
}

void		vct2_print(t_vct2 vct)
{
	ft_putstr("vector x : ");
	ft_putnbr(vct.x);
	ft_putstr(" y : ");
	ft_putnbrcr(vct.y);
}
