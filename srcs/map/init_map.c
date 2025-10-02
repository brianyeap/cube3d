/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:48:01 by brian             #+#    #+#             */
/*   Updated: 2025/10/02 16:20:21 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	init_map(void *brain, void *og_map)
{
	t_brain	*b;
	t_type	*og_map2;

	b = (t_brain *)brain;
	og_map2 = (t_type *)og_map;
	b->map = ch_m(malloc(sizeof(t_map)), brain,
			"\n\nError\nMalloc Error for Map");
	b->map->height = 0;
	b->map->width = 0;
	b->map->grid = NULL;
	b->map->bloc_size = 64;
	b->map->w_n = NULL;
	b->map->w_e = NULL;
	b->map->w_s = NULL;
	b->map->w_w = NULL;
	b->map->f_rgb = og_map2->f_rgb;
	b->map->c_rgb = og_map2->c_rgb;
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

t_player_detect	*chr_trt(char *line)
{
	t_player_detect	*player;
	int				i;
	int				found;

	i = 0;
	found = 0;
	player = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			line[i] = '0' - 1;
		else if (line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'W')
		{
			if (found == 1)
				exit_cube(NULL, "\n\nError\nMultiple players found", 0);
			found = set_player(&player, i, line, i);
		}
		else if (line[i] != '0' && line[i] != '1')
			exit_cube(NULL, "\n\nError\nInvalid character in map", 0);
		i++;
	}
	return (player);
}

t_player_detect	*add_map_row(t_map *m, char *line)
{
	t_player_detect	*player;

	player = chr_trt(line);
	realloc_map(m, line);
	return (player);
}
