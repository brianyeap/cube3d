/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:54 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 14:58:04 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

int	cell_at(t_brain *b, int mx, int my)
{
	t_map		*w;
	t_map_line	*row;

	if (!b || !b->rc || !b->rc->world)
		return (1);
	w = b->rc->world;
	if (my < 0 || my >= w->height)
		return (1);
	row = w->grid[my];
	if (!row)
		return (1);
	if (mx < 0 || mx >= row->length)
		return (1);
	return (row->line[mx]);
}

int	is_blocking(int v)
{
	return (v == 1);
}

int	hit(t_brain *b, float x, float y)
{
	int	mx;
	int	my;

	if (!b || !b->rc)
		return (1);
	mx = (int)(x / (float)b->rc->tile);
	my = (int)(y / (float)b->rc->tile);
	return (is_blocking(cell_at(b, mx, my)));
}
