/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:26:12 by tbottini          #+#    #+#             */
/*   Updated: 2019/02/09 17:12:39 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vct3		*vct3_new(int x, int y, int z)
{
	t_vct3	*new_vct3;

	if (!(new_vct3 = (t_vct3 *)malloc(sizeof(t_vct3))))
		return (NULL);
	new_vct3->x = x;
	new_vct3->y = y;
	new_vct3->z = z;
	return (new_vct3);
}

t_vct3		*vct3_value(t_vct3 *vct, int x, int y, int z)
{
	vct->x = x;
	vct->y = y;
	vct->z = z;
	return (vct);
}

t_vct3		*vct3_cpy(t_vct3 *vct1, t_vct3 *vct2)
{
	vct1->x = vct2->x;
	vct1->y = vct2->y;
	vct1->z = vct2->z;
	return (vct1);
}

t_vct3		*vct3_mul(t_vct3 *vct1, int mul)
{
	vct1->x *= mul;
	vct1->y *= mul;
	vct1->z *= mul;
	return (vct1);
}

t_vct3		*vct3_negate(t_vct3 *vct)
{
	vct->x -= vct->x;
	vct->y -= vct->y;
	vct->z -= vct->z;
	return (vct);
}
