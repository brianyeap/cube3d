/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:36:13 by brian             #+#    #+#             */
/*   Updated: 2025/09/29 14:32:40 by brian            ###   ########.fr       */
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

	dist = calculate_dist(b->ray->pos_x, b->ray->pos_y, ray_x, ray_y);
	return (dist * cos(ray_angle - b->rc->pa));
}
