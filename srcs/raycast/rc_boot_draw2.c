/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:56:57 by jow               #+#    #+#             */
/*   Updated: 2025/09/26 18:27:32 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	perform_dda(t_brain *b)
{
	if (b->ray->sideDistX < b->ray->sideDistY)
	{
		b->ray->sideDistX += b->ray->deltaDistX;
		b->ray->mapX += b->ray->stepX;
		b->ray->side = 0;
	}
	else
	{
		b->ray->sideDistY += b->ray->deltaDistY;
		b->ray->mapY += b->ray->stepY;
		b->ray->side = 1;
	}
	if (b->ray->mapX < 0 || b->ray->mapX >= b->map->width || \
b->ray->mapY < 0 || b->ray->mapY >= b->map->height)
	{
		b->ray->outOfBounds = 1;
		b->ray->hit = 1;
	}
	else if (cell_at(b, b->ray->mapX, b->ray->mapY) > 0)
		b->ray->hit = 1;
}

void	calculate_step(t_brain *b)
{
	if (b->ray->rayDirX < 0)
	{
		b->ray->stepX = -1;
		b->ray->sideDistX = (b->ray->posX - b->ray->mapX) * b->ray->deltaDistX;
	}
	else
	{
		b->ray->stepX = 1;
		b->ray->sideDistX = (b->ray->mapX + 1.0 - b->ray->posX) * \
b->ray->deltaDistX;
	}
	if (b->ray->rayDirY < 0)
	{
		b->ray->stepY = -1;
		b->ray->sideDistY = (b->ray->posY - b->ray->mapY) * b->ray->deltaDistY;
	}
	else
	{
		b->ray->stepY = 1;
		b->ray->sideDistY = (b->ray->mapY + 1.0 - b->ray->posY) * \
b->ray->deltaDistY;
	}
}

void	ray_setup(t_brain *b, int x)
{
	b->ray->cameraX = 2.0 * x / (double)WIN_W - 1.0;
	b->ray->rayDirX = b->ray->dirX + b->ray->planeX * b->ray->cameraX;
	b->ray->rayDirY = b->ray->dirY + b->ray->planeY * b->ray->cameraX;
	b->ray->mapX = (int)b->ray->posX;
	b->ray->mapY = (int)b->ray->posY;
	if (b->ray->rayDirX == 0.0)
		b->ray->deltaDistX = 1e30;
	else
		b->ray->deltaDistX = fabs(1.0 / b->ray->rayDirX);
	if (b->ray->rayDirY == 0.0)
		b->ray->deltaDistY = 1e30;
	else
		b->ray->deltaDistY = fabs(1.0 / b->ray->rayDirY);
}

void	init_dda(t_brain *b)
{
	b->ray->fov = M_PI / 3.0;
	b->ray->posX = b->rc->px / (double)b->map->bloc_size;
	b->ray->posY = b->rc->py / (double)b->map->bloc_size;
	b->ray->dirX = cos(b->rc->pa);
	b->ray->dirY = sin(b->rc->pa);
	b->ray->planeLen = tan(b->ray->fov / 2.0);
	b->ray->planeX = -b->ray->dirY * b->ray->planeLen;
	b->ray->planeY = b->ray->dirX * b->ray->planeLen;
}

void	perform_raycast(t_brain *b, int x)
{
	int	safety;

	ray_setup(b, x);
	calculate_step(b);
	b->ray->hit = 0;
	b->ray->outOfBounds = 0;
	safety = 0;
	while (!b->ray->hit && safety++ < 2048)
		perform_dda(b);
}
/*
planeLen is half the width of the camera plane.
*/
