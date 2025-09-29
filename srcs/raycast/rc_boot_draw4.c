/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:01:43 by jow               #+#    #+#             */
/*   Updated: 2025/09/28 21:38:42 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	render_sky(t_brain *b, int x)
{
	int	y;

	y = 0;
	while (y < b->ray->drawStart)
		put_px(b, x, y++, b->map->c_rgb);
}

void	render_wall_texture(t_brain *b, int x)
{
	int	y;
	int	tex_y;
	int	color;

	b->ray->step = (double)b->rc->tile / (double)b->ray->lineHeight;
	b->ray->texPos = (double)(b->ray->drawStart - b->ray->drawStart0) \
* b->ray->step;
	y = b->ray->drawStart;
	while (y < b->ray->drawEnd)
	{
		tex_y = (int)b->ray->texPos;
		color = get_texture_pixel(b, b->ray->texX, tex_y);
		put_px(b, x, y, color);
		b->ray->texPos += b->ray->step;
		y++;
	}
}

void	render_floor(t_brain *b, int x)
{
	int	y;

	y = b->ray->drawEnd;
	while (y < WIN_H)
		put_px(b, x, y++, b->map->f_rgb);
}
