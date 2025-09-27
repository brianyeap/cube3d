/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:35 by brian             #+#    #+#             */
/*   Updated: 2025/09/26 18:38:15 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	clear_img(t_brain *b)
{
	int	y;
	int	x;

	y = 0;
	while (y < b->rc->h)
	{
		x = 0;
		while (x < b->rc->w)
		{
			put_px(b, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	get_rgb(t_buff *tex, int tex_x, int tex_y)
{
	int				index;
	unsigned char	*data;
	unsigned char	bb;
	unsigned char	g;
	unsigned char	r;

	if (!tex || tex_x < 0 || tex_x >= tex->width || \
tex_y < 0 || tex_y >= tex->height)
		return (0xFFFFFF);
	if (tex->offset < 3)
		return (0xFFFFFF);
	index = tex_y * tex->line_length + tex_x * tex->offset;
	data = (unsigned char *)tex->addr;
	bb = data[index + 0];
	g = data[index + 1];
	r = data[index + 2];
	return ((r << 16) | (g << 8) | bb);
}

/*
side == 0: vertical wall (east/west)
rayDirX > 0: east wall
rayDirX < 0: west wall

side == 1: horizontal wall (north/south)
rayDirY > 0: south wall
rayDirY < 0: north wall
*/

int	get_texture_pixel(t_brain *b, int tex_x, int tex_y)
{
	t_buff	*tex;

	tex = NULL;
	if (b->ray->side == 0)
	{
		if (b->ray->rayDirX > 0)
			tex = b->map->w_e;
		else
			tex = b->map->w_w;
	}
	else
	{
		if (b->ray->rayDirY > 0)
			tex = b->map->w_s;
		else
			tex = b->map->w_n;
	}
	return (get_rgb(tex, tex_x, tex_y));
}

void	render_out_of_bounds(t_brain *b, int x)
{
	int	mid;
	int	y;

	y = 0;
	mid = WIN_H / 2;
	while (y < mid)
		put_px(b, x, y++, b->map->c_rgb);
	while (y < WIN_H)
		put_px(b, x, y++, b->map->f_rgb);
}

void	draw_3d(t_brain *b)
{
	int	x;

	init_dda(b);
	x = 0;
	while (x < WIN_W)
	{
		perform_raycast(b, x);
		if (b->ray->outOfBounds)
		{
			render_out_of_bounds(b, x);
			x++;
			continue ;
		}
		calc_perp_wall(b);
		calculate_wall_rendering(b);
		render_sky(b, x);
		render_wall_texture(b, x);
		render_floor(b, x);
		x++;
	}
}
