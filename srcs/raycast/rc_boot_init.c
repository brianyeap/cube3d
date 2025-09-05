/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:23:20 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 15:11:18 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

int	rc_boot_init(t_brain *b)
{
	if (!b || !b->ctx || !b->ctx->mlx_ptr || !b->ctx->win_ptr)
		return (-1);
	b->rc = malloc(sizeof(*b->rc));
	if (!b->rc)
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

void	rc_boot_attach_world(t_brain *b)
{
	if (!b || !b->map || !b->player || !b->rc)
		return ;
	b->rc->world = b->map;
	b->rc->tile = b->map->bloc_size;
	b->rc->px = (float)b->player->position->x;
	b->rc->py = (float)b->player->position->y;
	b->rc->pa = (float)b->player->angle;
	b->rc->pdx = cosf(b->rc->pa) * 5.0f;
	b->rc->pdy = sinf(b->rc->pa) * 5.0f;
}
