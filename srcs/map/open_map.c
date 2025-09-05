/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:46:46 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 18:27:08 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	free_player_close_file(t_player_detect *player, int fd)
{
	free(player);
	close(fd);
}

void	get_map(t_brain *b, char *map_path)
{
	t_player_detect	*player;
	int				ret;
	int				file;
	char			*line;

	file = open(map_path, O_RDONLY);
	ret = get_next_line(file, &line);
	while (ret && ((ft_strmultichr(line, " 01SNEW")) != 1))
	{
		free(line);
		ret = get_next_line(file, &line);
	}
	while (ret != -1)
	{
		player = add_map_row(b->map, line);
		if (player)
		{
			init_player(b, player->pos_x, player->direction);
			free(player);
		}
		if (!ret)
			break ;
		ret = get_next_line(file, &line);
	}
	free_player_close_file(player, file);
}

void	free_map_check(t_type *map)
{
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map->s);
	free(map->f);
	free(map->c);
	free(map);
}

int	open_map(t_brain *b, char *map_path, t_type *map)
{
	init_map(b);
	init_textures(b, map);
	get_map(b, map_path);
	sort_sprites(b->player->position, b->map->sprites);
	ft_printf(CYAN"	-> Width: [%d]\n", b->map->width);
	ft_printf(CYAN"	-> Height:[%d]\n\n"RST, b->map->height);
	b->map->px_width = b->map->width * b->map->bloc_size;
	b->map->px_height = b->map->height * b->map->bloc_size;
	dprintf(1, CYAN"\nReal Size : %d x %d px\n", b->map->px_width,
		b->map->px_height);
	free_map_check(map);
	return (1);
}

