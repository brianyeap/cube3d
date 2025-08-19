/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:30:48 by brian             #+#    #+#             */
/*   Updated: 2025/08/19 18:57:36 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLAYER_H
# define PLAYER_H
# include "cube3d.h"
# include "canvas.h"

typedef struct s_camera
{
	float		fov;
	t_fpoint	proj_size;
	float		proj_dist;
}				t_camera;

typedef struct s_player
{
	int			initialized;
	int			as_move;
	int			as_rotate;
	t_fpoint	*position;
	t_camera	*cam;
	float		angle;
	t_fpoint	*step;
	float		rot_speed;
	float		speed;
	float		divided;
	t_ctx		*ctx;
	void		*brain;
	void		(*rot)(struct s_player *, float);
	void		(*move)(struct s_player *, int);
	void		(*sidemove)(struct s_player *, int);
	void		(*draw)(struct s_player *, t_ctx *);
}				t_player;

int	init_player(t_brain *b, int pos_x, char angle);

#endif