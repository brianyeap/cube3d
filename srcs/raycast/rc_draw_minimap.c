/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:10 by jow               #+#    #+#             */
/*   Updated: 2025/09/26 19:58:04 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void	draw_scaled_cell(t_brain *b, int x, int y, int colour)
{
	int	px_y_start;
	int	px_x_end;
	int	px_y_end;
	int	i;
	int	j;

	px_y_start = 5 + (int)(y * b->ray->scale_y);
	px_x_end = 5 + (int)((x + 1) * b->ray->scale_x);
	px_y_end = 5 + (int)((y + 1) * b->ray->scale_y);
	i = b->ray->px_x_start;
	while (i < px_x_end)
	{
		j = px_y_start;
		while (j < px_y_end)
		{
			put_px(b, i, j, colour);
			j++;
		}
		i++;
	}
}

int	get_cell_colour(t_brain *b, int x, int y)
{
	int	cell;

	cell = cell_at(b, x, y);
	if (cell == 1 || cell == -1)
		return (0x000000);
	else
		return (0xFFFFFF);
}

void	draw_minimap(t_brain *b, int minimap_size)
{
	int	x;
	int	y;
	int	colour;

	b->ray->scale_x = (float)minimap_size / (float)b->map->width;
	b->ray->scale_y = (float)minimap_size / (float)b->map->height;
	y = 0;
	while (y < b->map->height)
	{
		x = 0;
		while (x < b->map->width)
		{
			colour = get_cell_colour(b, x, y);
			b->ray->px_x_start = 5 + (int)(x * b->ray->scale_x);
			draw_scaled_cell(b, x, y, colour);
			x++;
		}
		y++;
	}
}

void	draw_miniplayer(t_brain *b, int minimap_size)
{
	float	p_grid_x;
	float	p_grid_y;
	int		p_minimap_x;
	int		p_minimap_y;

	p_grid_x = b->rc->px / (float)b->map->bloc_size;
	p_grid_y = b->rc->py / (float)b->map->bloc_size;
	p_minimap_x = 5 + (int)((p_grid_x / b->map->width) * minimap_size);
	p_minimap_y = 5 + (int)((p_grid_y / b->map->height) * minimap_size);
	put_px(b, p_minimap_x, p_minimap_y, 0xFF0000);
	put_px(b, p_minimap_x - 1, p_minimap_y - 1, 0xFF0000);
	put_px(b, p_minimap_x, p_minimap_y - 1, 0xFF0000);
	put_px(b, p_minimap_x + 1, p_minimap_y - 1, 0xFF0000);
	put_px(b, p_minimap_x - 1, p_minimap_y, 0xFF0000);
	put_px(b, p_minimap_x + 1, p_minimap_y, 0xFF0000);
	put_px(b, p_minimap_x - 1, p_minimap_y + 1, 0xFF0000);
	put_px(b, p_minimap_x, p_minimap_y + 1, 0xFF0000);
	put_px(b, p_minimap_x + 1, p_minimap_y + 1, 0xFF0000);
}

void	rc_draw_minimap(t_brain *b)
{
	int	minimap_size;

	minimap_size = 180;
	draw_minimap(b, minimap_size);
	draw_miniplayer(b, minimap_size);
}
