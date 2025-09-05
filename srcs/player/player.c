/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:54:50 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 17:09:30 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_player(t_brain *b, int pos_x, char angle)
{
	ft_printf(CYAN"	-> Init player at ");
	b->player = malloc(sizeof(t_player));
	if (b->player == NULL)
		exit_cube(NULL, "Failed to malloc player", 0);
	b->player->position = malloc(sizeof(t_fpoint));
	if (!b->player->position)
		exit_cube(NULL, "Failed to malloc player pos", 0);
	b->player->position->x = ((pos_x + 1) * b->map->bloc_size)
		- (b->map->bloc_size / 2);
	b->player->position->y = (b->map->height * b->map->bloc_size)
		- (b->map->bloc_size / 2);
	b->player->angle = get_player_angle(angle);
	ft_putstr(GRN"OK\n");
	ft_printf(GRN"Player init - "GRN"OK\n"RST);
	return (1);
}

float	get_player_angle(char dir)
{
	if (dir == 'N')
		return (2 * PI * 0.75);
	if (dir == 'E')
		return (0);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'W')
		return (PI);
	ft_putstr(RED"Unknown direction for get_player_angle - player.c\n"RST);
	return (0);
}
