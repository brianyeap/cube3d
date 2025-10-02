/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:58:12 by jow               #+#    #+#             */
/*   Updated: 2025/10/02 17:22:17 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	calc_perp_wall(t_brain *b)
{
	if (b->ray->side == 0)
		b->ray->perp_wall_dist = b->ray->side_dist_x - b->ray->delta_dist_x;
	else
		b->ray->perp_wall_dist = b->ray->side_dist_y - b->ray->delta_dist_y;
	if (b->ray->perp_wall_dist < 1e-6)
		b->ray->perp_wall_dist = 1e-6;
}

void	calculate_line_height(t_brain *b)
{
	b->ray->line_height = (int)((WIN_H * 2) / b->ray->perp_wall_dist);
	if (b->ray->line_height < 1)
		b->ray->line_height = 1;
}

void	calculate_draw_bounds(t_brain *b)
{
	b->ray->draw_start0 = (int)(WIN_H / 2 - b->ray->line_height / 2);
	b->ray->draw_end0 = b->ray->draw_start0 + b->ray->line_height;
	if (b->ray->draw_start0 < 0)
		b->ray->draw_start = 0;
	else
		b->ray->draw_start = b->ray->draw_start0;
	if (b->ray->draw_end0 > WIN_H)
		b->ray->draw_end = WIN_H;
	else
		b->ray->draw_end = b->ray->draw_end0;
}

void	calculate_texture_x(t_brain *b)
{
	if (b->ray->side == 0)
		b->ray->wall_x = b->ray->pos_y + b->ray->perp_wall_dist
			* b->ray->raydir_y;
	else
		b->ray->wall_x = b->ray->pos_x + b->ray->perp_wall_dist
			* b->ray->raydir_x;
	b->ray->wall_x -= floor(b->ray->wall_x);
	b->ray->tex_x = (int)(b->ray->wall_x * (double)b->rc->tile);
	if (b->ray->side == 0 && b->ray->raydir_x < 0)
		b->ray->tex_x = b->rc->tile - b->ray->tex_x - 1;
	if (b->ray->side == 1 && b->ray->raydir_y > 0)
		b->ray->tex_x = b->rc->tile - b->ray->tex_x - 1;
	if (b->ray->tex_x < 0)
		b->ray->tex_x = 0;
	if (b->ray->tex_x >= b->rc->tile)
		b->ray->tex_x = b->rc->tile - 1;
}

void	calculate_wall_rendering(t_brain *b)
{
	calculate_line_height(b);
	calculate_draw_bounds(b);
	calculate_texture_x(b);
}
