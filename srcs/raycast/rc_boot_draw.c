/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:35 by brian             #+#    #+#             */
/*   Updated: 2025/09/09 14:53:42 by brian            ###   ########.fr       */
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

static void	ray_init(t_brain *b, t_ray *r, float ang)
{
	r->ang = ang;
	r->rdx = cosf(ang);
	r->rdy = sinf(ang);
	r->rx = b->rc->px;
	r->ry = b->rc->py;
	r->steps = 0;
}

static void	ray_cast_until_hit(t_brain *b, t_ray *r, int max_steps)
{
	while (!hit(b, r->rx, r->ry) && r->steps < max_steps)
	{
		r->rx += r->rdx;
		r->ry += r->rdy;
		r->steps++;
	}
}

static void	draw_slice(t_brain *b, int col, const t_ray *r)
{
	float	d;
	float	h;
	int		sy;
	int		ey;

	d = fixed_dist(b, r->rx, r->ry, r->ang);
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
		put_px(b, col, sy++, 0x0000FF);
}

void	draw_3d(t_brain *b)
{
	float	fov;
	float	step;
	float	start;
	int		col;
	t_ray	r;

	fov = (float)M_PI / 3.0f;
	step = fov / (float)b->rc->w;
	start = b->rc->pa - fov * 0.5f;
	col = 0;
	while (col < b->rc->w)
	{
		ray_init(b, &r, start + (float)col * step);
		ray_cast_until_hit(b, &r, 300);
		draw_slice(b, col, &r);
		col++;
	}
}
