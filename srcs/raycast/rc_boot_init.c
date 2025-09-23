/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:23:20 by brian             #+#    #+#             */
/*   Updated: 2025/09/24 00:05:14 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

int rc_boot_init(t_brain *b)
{
	if (!b || !b->ctx || !b->ctx->mlx_ptr || !b->ctx->win_ptr)
		return (-1);
	b->rc = malloc(sizeof(*b->rc));
	if (!b->rc)
		return (-1);
	b->ray = malloc(sizeof(t_ray));
	if (!b->ray)
		return (-1);
	b->rc->w = 1024;
	b->rc->h = 512;
	b->rc->img = mlx_new_image(b->ctx->mlx_ptr, b->rc->w, b->rc->h);
	if (!b->rc->img)
	{
		free(b->rc);
		b->rc = NULL;
		return (-1);
	}
	b->rc->data = mlx_get_data_addr(b->rc->img,
									&b->rc->bpp, &b->rc->stride, &b->rc->endian);
	b->rc->pa = 0.0f;
	b->rc->pdx = cosf(b->rc->pa) * 5.0f;
	b->rc->pdy = sinf(b->rc->pa) * 5.0f;
	b->rc->tile = 64;
	b->rc->world = NULL;
	return (0);
}

void rc_boot_attach_world(t_brain *b)
{
	if (!b || !b->map || !b->player || !b->rc)
		return;
	b->rc->world = b->map;
	b->rc->tile = b->map->bloc_size;
	b->rc->px = (float)b->player->position->x;
	b->rc->py = (float)b->player->position->y;
	b->rc->pa = (float)b->player->angle;
	b->rc->pdx = cosf(b->rc->pa) * 5.0f;
	b->rc->pdy = sinf(b->rc->pa) * 5.0f;
}

void put_px(t_brain *b, int x, int y, int color)
{
	int i;

	if (!b || !b->rc)
		return;
	if (x < 0 || x >= b->rc->w || y < 0 || y >= b->rc->h)
		return;
	i = y * b->rc->stride + x * (b->rc->bpp / 8);
	b->rc->data[i + 0] = color & 0xFF;
	b->rc->data[i + 1] = (color >> 8) & 0xFF;
	b->rc->data[i + 2] = (color >> 16) & 0xFF;
}
