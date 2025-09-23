/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:36:13 by brian             #+#    #+#             */
/*   Updated: 2025/09/23 23:49:32 by jow              ###   ########.fr       */
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

float calcDist(const float ax, const float ay, const float bx, const float by)
{
    return (sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
}

float fixed_dist(float player_x, float player_y, float ray_x, float ray_y, float ray_angle, t_brain *b)
{
    float dist = calcDist(player_x, player_y, ray_x, ray_y);
    return (dist * cos(ray_angle - b->rc->pa)); // Fix fisheye effect
}
