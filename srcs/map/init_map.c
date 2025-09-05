/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:48:01 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 17:44:02 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_map(t_ctx *ctx, void *brain)
{
	t_brain	*b;

	b = (t_brain *)brain;
	b->map = ch_m(malloc(sizeof(t_map)), brain, "Malloc Error for Map");
	b->map->height = 0;
	b->map->width = 0;
	b->map->grid = NULL;
	b->map->scale = 1;
	b->map->bloc_size = 64;
	b->map->w_n = NULL;
	b->map->w_e = NULL;
	b->map->w_s = NULL;
	b->map->w_w = NULL;
	b->map->floor = NULL;
	b->map->sprites = ch_m(malloc(sizeof(t_spr_list)), brain,
			"malloc fail for sprite list");
	b->map->sprites->column = ch_m(malloc(b->ctx->width * sizeof(float)), brain,
			"malloc failed for distance array");
	b->map->sprites->length = 0;
	b->map->sprites->list = NULL;
	b->map->skybox = NULL;
	b->map->brain = b;
	return (1);
}

void	init_textures(t_brain *b, t_type *map)
{
	ft_putstr(CYAN"Init Textures\n");
	init_texture(b, map->no, &b->map->w_n);
	init_texture(b, map->ea, &b->map->w_e);
	init_texture(b, map->so, &b->map->w_s);
	init_texture(b, map->we, &b->map->w_w);
	init_texture(b, map->f, &b->map->floor);
	init_texture(b, map->c, &b->map->skybox);
}

int	realloc_map(t_map *m, char *line)
{
	t_map_line	**grid;
	int			y;
	int			len;

	len = ft_strlen(line);
	if (len > m->width)
		m->width = len;
	y = 0;
	grid = ft_calloc(m->height + 1, sizeof(t_map_line *));
	while (y < m->height)
	{
		grid[y] = m->grid[y];
		y++;
	}
	grid[y] = malloc(sizeof(t_map_line));
	grid[y]->length = len;
	grid[y]->line = ft_str_to_int_tab(line);
	free(line);
	free(m->grid);
	m->grid = grid;
	m->height++;
	return (1);
}

t_player_detect	*chr_trt(char *line, t_map *m)
{
	t_player_detect	*player;
	int				i;
	int				real;

	i = 0;
	real = 0;
	player = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			line[i] = '0' - 1;
		if (line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'W')
		{
			player = malloc(sizeof(t_player_detect));
			player->pos_x = i;
			player->direction = line[i];
		}
		real = line[i] - '0';
		if (real == 2)
			add_spr_to_list(m->sprites,
				init_sprite(m, new_fpoint(i, m->height), real));
		i++;
	}
	return (player);
}

t_player_detect	*add_map_row(t_map *m, char *line)
{
	t_player_detect	*player;

	player = chr_trt(line, m);
	realloc_map(m, line);
	return (player);
}
