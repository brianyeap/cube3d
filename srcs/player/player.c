/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:54:50 by brian             #+#    #+#             */
/*   Updated: 2025/08/29 15:57:57 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_cam(t_brain *b)
{
	t_camera	*cam;

	b->player->cam = malloc(sizeof(t_camera));
	cam = b->player->cam;
	cam->fov = ft_inrad(60);
	cam->proj_size.x = b->ctx->width;
	cam->proj_size.y = b->ctx->height;
	cam->proj_dist = (cam->proj_size.x / 2) / tan(cam->fov / 2);
	return (1);
}

int	init_values(t_brain *b, t_player *p)
{
	// Joe do
	// p->move = &move;
	// p->sidemove = &side_move;
	// p->rot = &rotate;
	p->speed = b->map->bloc_size * 0.12;
	p->rot_speed = (3 * PI) / 180;
	p->step = malloc(sizeof(t_fpoint *));
	if (p->step == NULL)
		exit_cube(NULL, "Failed: malloc player step", 0);
	p->brain = b;
	p->as_move = 1;
	p->as_rotate = 1;
	p->initialized = 1;
	return (1);
}

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
	init_cam(b);
	init_values(b, b->player);
	b->player->angle = get_player_angle(angle);
	// b->player->rot(b->player, 0); joe do
	b->player->ctx = b->ctx;
	b->ctx->col_step = b->player->cam->fov / b->ctx->width;
	ft_putstr("	-> Init Cam - ");
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
