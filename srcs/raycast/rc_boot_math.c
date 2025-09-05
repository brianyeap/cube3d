/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:36:13 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 14:54:48 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"


float distf(float ax, float ay, float bx, float by)
{
    float dx = ax - bx;
    float dy = ay - by;
    return sqrtf(dx * dx + dy * dy);
}

float fixed_dist(t_brain *b, float rx, float ry, float ray_ang)
{
  float d = distf(b->rc->px, b->rc->py, rx, ry);
  return d * cosf(ray_ang - b->rc->pa);
}