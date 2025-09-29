/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:01:43 by jow               #+#    #+#             */
/*   Updated: 2025/09/29 14:36:00 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	render_sky(t_brain *b, int x)
{
	int	y;

	y = 0;
	while (y < b->ray->draw_start)
		put_px(b, x, y++, b->map->c_rgb);
}

void	render_wall_texture(t_brain *b, int x)
{
	int	y;
	int	tex_y;
	int	color;

	b->ray->step = (double)b->rc->tile / (double)b->ray->line_height;
	b->ray->tex_pos = (double)(b->ray->draw_start - b->ray->draw_start0) \
* b->ray->step;
	y = b->ray->draw_start;
	while (y < b->ray->draw_end)
	{
		tex_y = (int)b->ray->tex_pos;
		color = get_texture_pixel(b, b->ray->tex_x, tex_y);
		put_px(b, x, y, color);
		b->ray->tex_pos += b->ray->step;
		y++;
	}
}

void	render_floor(t_brain *b, int x)
{
	int	y;

	y = b->ray->draw_end;
	while (y < WIN_H)
		put_px(b, x, y++, b->map->f_rgb);
}
