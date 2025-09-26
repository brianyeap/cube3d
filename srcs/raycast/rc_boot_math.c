/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:36:13 by brian             #+#    #+#             */
/*   Updated: 2025/09/26 18:49:06 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

float	distf(float ax, float ay, float bx, float by)
{
	float	dx;
	float	dy;

	dx = ax - bx;
	dy = ay - by;
	return (sqrtf(dx * dx + dy * dy));
}

float	calculate_dist(const float ax, const float ay, const float bx,
				const float by)
{
	return (sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
}

float	fixed_dist(float ray_x, float ray_y, float ray_angle, t_brain *b)
{
	float	dist;

	dist = calculate_dist(b->ray->posX, b->ray->posY, ray_x, ray_y);
	return (dist * cos(ray_angle - b->rc->pa));
}
