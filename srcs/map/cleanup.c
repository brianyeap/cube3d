/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:28:21 by brian             #+#    #+#             */
/*   Updated: 2025/10/02 17:49:24 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "map.h"

static void	free_map_grid(t_map *m)
{
	int	y;

	y = 0;
	while (y < m->height)
	{
		if (m->grid[y])
		{
			free(m->grid[y]->line);
			free(m->grid[y]);
		}
		y++;
	}
	free(m->grid);
}

void	clean_up(t_brain *b)
{
	if (b)
	{
		mlx_destroy_image(b->ctx->mlx_ptr, b->map->w_n->img);
		mlx_destroy_image(b->ctx->mlx_ptr, b->map->w_s->img);
		mlx_destroy_image(b->ctx->mlx_ptr, b->map->w_e->img);
		mlx_destroy_image(b->ctx->mlx_ptr, b->map->w_w->img);
		mlx_destroy_image(b->ctx->mlx_ptr, b->rc->img);
		mlx_destroy_window(b->ctx->mlx_ptr, b->ctx->win_ptr);
		free(b->ctx->mlx_ptr);
		free(b->ctx);
		if (b->player)
			cleanup_free_player(b);
		free(b->keys);
		free(b->rc);
		free(b->ray);
		free(b->map->w_n);
		free(b->map->w_s);
		free(b->map->w_e);
		free(b->map->w_w);
		free_map_grid(b->map);
		free(b->map);
		free(b);
	}
}

void	exit_cube(t_brain *brain, char *msg, int exit_now)
{
	static t_brain	*b = NULL;

	if (b == NULL && brain != NULL)
	{
		b = brain;
		ft_putstr("Stored brain pointer\n");
	}
	if (exit_now)
		return ;
	ft_putstr(RED"\nCub3D Exit: ");
	ft_putstr(msg);
	ft_putstr(RST"\n");
	clean_up(b);
	ft_putstr(YELO"Clean Up OK\n"RST);
	ft_putstr(BLUE"Exit Done\n"RST);
	exit(0);
}

void	free_map_check(t_type *map)
{
	if (!map)
		return ;
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map);
}
