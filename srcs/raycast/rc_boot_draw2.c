/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:56:57 by jow               #+#    #+#             */
/*   Updated: 2025/09/29 14:34:48 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	perform_dda(t_brain *b)
{
	if (b->ray->side_dist_x < b->ray->side_dist_y)
	{
		b->ray->side_dist_x += b->ray->delta_dist_x;
		b->ray->map_x += b->ray->step_x;
		b->ray->side = 0;
	}
	else
	{
		b->ray->side_dist_y += b->ray->delta_dist_y;
		b->ray->map_y += b->ray->step_y;
		b->ray->side = 1;
	}
	if (b->ray->map_x < 0 || b->ray->map_x >= b->map->width || \
b->ray->map_y < 0 || b->ray->map_y >= b->map->height)
	{
		b->ray->out_of_bounds = 1;
		b->ray->hit = 1;
	}
	else if (cell_at(b, b->ray->map_x, b->ray->map_y) > 0)
		b->ray->hit = 1;
}

void	calculate_step(t_brain *b)
{
	if (b->ray->raydir_x < 0)
	{
		b->ray->step_x = -1;
		b->ray->side_dist_x = (b->ray->pos_x - b->ray->map_x) * b->ray->delta_dist_x;
	}
	else
	{
		b->ray->step_x = 1;
		b->ray->side_dist_x = (b->ray->map_x + 1.0 - b->ray->pos_x) * \
b->ray->delta_dist_x;
	}
	if (b->ray->raydir_y < 0)
	{
		b->ray->step_y = -1;
		b->ray->side_dist_y = (b->ray->pos_y - b->ray->map_y) * b->ray->delta_dist_y;
	}
	else
	{
		b->ray->step_y = 1;
		b->ray->side_dist_y = (b->ray->map_y + 1.0 - b->ray->pos_y) * \
b->ray->delta_dist_y;
	}
}

void	ray_setup(t_brain *b, int x)
{
	b->ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	b->ray->raydir_x = b->ray->dir_x + b->ray->plane_x * b->ray->camera_x;
	b->ray->raydir_y = b->ray->dir_y + b->ray->plane_y * b->ray->camera_x;
	b->ray->map_x = (int)b->ray->pos_x;
	b->ray->map_y = (int)b->ray->pos_y;
	if (b->ray->raydir_x == 0.0)
		b->ray->delta_dist_x = 1e30;
	else
		b->ray->delta_dist_x = fabs(1.0 / b->ray->raydir_x);
	if (b->ray->raydir_y == 0.0)
		b->ray->delta_dist_y = 1e30;
	else
		b->ray->delta_dist_y = fabs(1.0 / b->ray->raydir_y);
}

void	init_dda(t_brain *b)
{
	b->ray->fov = M_PI / 3.0;
	b->ray->pos_x = b->rc->px / (double)b->map->bloc_size;
	b->ray->pos_y = b->rc->py / (double)b->map->bloc_size;
	b->ray->dir_x = cos(b->rc->pa);
	b->ray->dir_y = sin(b->rc->pa);
	b->ray->plane_len = tan(b->ray->fov / 2.0);
	b->ray->plane_x = -b->ray->dir_y * b->ray->plane_len;
	b->ray->plane_y = b->ray->dir_x * b->ray->plane_len;
}

void	perform_raycast(t_brain *b, int x)
{
	int	safety;

	ray_setup(b, x);
	calculate_step(b);
	b->ray->hit = 0;
	b->ray->out_of_bounds = 0;
	safety = 0;
	while (!b->ray->hit && safety++ < 2048)
		perform_dda(b);
}
/*
plane_len is half the width of the camera plane.
*/
