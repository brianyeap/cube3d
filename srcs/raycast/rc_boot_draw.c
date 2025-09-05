/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:35 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 15:15:19 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	put_px(t_brain *b, int x, int y, int color)
{
	int	i;

	if (!b || !b->rc)
		return ;
	if (x < 0 || x >= b->rc->w || y < 0 || y >= b->rc->h)
		return ;
	i = y * b->rc->stride + x * (b->rc->bpp / 8);
	b->rc->data[i + 0] = color & 0xFF;
	b->rc->data[i + 1] = (color >> 8) & 0xFF;
	b->rc->data[i + 2] = (color >> 16) & 0xFF;
}

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


void	draw_3d(t_brain *b)
{
	float	fov;
	float	step;
	float	start;
	int		col;

	float	ang;
	float	rdx;
	float	rdy;
	float	rx;
	float	ry;
	int		steps;

	fov = (float)M_PI / 3.0f;
	step = fov / (float)b->rc->w;
	start = b->rc->pa - fov * 0.5f;
	col = 0;
	while (col < b->rc->w)
	{
		ang = start + (float)col * step;
		rdx = cosf(ang);
		rdy = sinf(ang);
		rx = b->rc->px;
		ry = b->rc->py;
		steps = 0;

		while (!hit(b, rx, ry) && steps < 300)
		{
			rx += rdx;
			ry += rdy;
			steps++;
		}
		{
			float d = fixed_dist(b, rx, ry, ang);
			float h;
			int   sy;
			int   ey;

			if (d < 0.001f)
				d = 0.001f;
			h = ((float)b->rc->tile / d) * (b->rc->w * 0.5f);
			sy = (int)((b->rc->h - h) * 0.5f);
			ey = sy + (int)h;
			if (sy < 0)
				sy = 0;
			if (ey > b->rc->h)
				ey = b->rc->h;
			while (sy < ey)
			{
				put_px(b, col, sy, 0x0000FF);
				sy++;
			}
		}
		col++;
	}
}
