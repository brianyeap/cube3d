/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:58:12 by jow               #+#    #+#             */
/*   Updated: 2025/09/28 21:38:33 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	calc_perp_wall(t_brain *b)
{
	double	denom;

	if (b->ray->side == 0)
	{
		if (b->ray->rayDirX == 0.0)
			denom = 1e-9;
		else
			denom = b->ray->rayDirX;
		b->ray->perpWallDist = (b->ray->mapX - b->ray->posX + \
(1 - b->ray->stepX) / 2.0) / denom;
	}
	else
	{
		if (b->ray->rayDirY == 0.0)
			denom = 1e-9;
		else
			denom = b->ray->rayDirY;
		b->ray->perpWallDist = (b->ray->mapY - b->ray->posY + \
(1 - b->ray->stepY) / 2.0) / denom;
	}
	if (b->ray->perpWallDist < 1e-6)
		b->ray->perpWallDist = 1e-6;
}

void	calculate_line_height(t_brain *b)
{
	b->ray->lineHeight = (int)(WIN_H / b->ray->perpWallDist);
	if (b->ray->lineHeight < 1)
		b->ray->lineHeight = 1;
}

void	calculate_draw_bounds(t_brain *b)
{
	b->ray->drawStart0 = (int)(WIN_H / 2 - b->ray->lineHeight / 2);
	b->ray->drawEnd0 = b->ray->drawStart0 + b->ray->lineHeight;
	if (b->ray->drawStart0 < 0)
		b->ray->drawStart = 0;
	else
		b->ray->drawStart = b->ray->drawStart0;
	if (b->ray->drawEnd0 > WIN_H)
		b->ray->drawEnd = WIN_H;
	else
		b->ray->drawEnd = b->ray->drawEnd0;
}

void	calculate_texture_x(t_brain *b)
{
	if (b->ray->side == 0)
		b->ray->wallX = b->ray->posY + b->ray->perpWallDist * b->ray->rayDirY;
	else
		b->ray->wallX = b->ray->posX + b->ray->perpWallDist * b->ray->rayDirX;
	b->ray->wallX -= floor(b->ray->wallX);
	b->ray->texX = (int)(b->ray->wallX * (double)b->rc->tile);
	if (b->ray->side == 0 && b->ray->rayDirX < 0)
		b->ray->texX = b->rc->tile - b->ray->texX - 1;
	if (b->ray->side == 1 && b->ray->rayDirY > 0)
		b->ray->texX = b->rc->tile - b->ray->texX - 1;
	if (b->ray->texX < 0)
		b->ray->texX = 0;
	if (b->ray->texX >= b->rc->tile)
		b->ray->texX = b->rc->tile - 1;
}

void	calculate_wall_rendering(t_brain *b)
{
	calculate_line_height(b);
	calculate_draw_bounds(b);
	calculate_texture_x(b);
}
