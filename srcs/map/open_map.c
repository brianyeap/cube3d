/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:46:46 by brian             #+#    #+#             */
/*   Updated: 2025/09/25 17:15:58 by jow              ###   ########.fr       */
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

	player = NULL;
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
			init_and_free_player(b, player->pos_x, player->direction, player);
		if (!ret)
			break ;
		ret = get_next_line(file, &line);
	}
	if (!b->player)
		info_and_exit(b, "No player Found!", "\n\nError\nNo player found");
	free_player_close_file(player, file);
}

void	init_and_free_player(t_brain *b, int x, char g, t_player_detect *p)
{
	if (!p)
		return ;
	if (b->player)
		info_and_exit(b, "Multiple player positions detected in map.",
			"\n\nError\nMultiple players found");
	init_player(b, x, g);
	free(p);
}

void	info_and_exit(t_brain *b, char *infoMsg, char *exitMsg)
{
	ft_printf("%s\n", infoMsg);
	exit_cube(b, exitMsg, 0);
}

int	open_map(t_brain *b, char *map_path, t_type *map)
{
	init_map(b, map);
	init_textures(b, map);
	get_map(b, map_path);
	ft_printf(CYAN"	-> Width: [%d]\n", b->map->width);
	ft_printf(CYAN"	-> Height:[%d]\n\n"RST, b->map->height);
	free_map_check(map);
	return (1);
}
