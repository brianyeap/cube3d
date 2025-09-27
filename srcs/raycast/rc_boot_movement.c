/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:03:22 by brian             #+#    #+#             */
/*   Updated: 2025/09/26 18:41:09 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

int	rc_boot_key_up(t_brain *b)
{
	float	nx;
	float	ny;

	nx = b->rc->px + b->rc->pdx;
	ny = b->rc->py + b->rc->pdy;
	if (!hit(b, nx, ny))
	{
		b->rc->px = nx;
		b->rc->py = ny;
	}
	return (0);
}

int	rc_boot_key_down(t_brain *b)
{
	float	nx;
	float	ny;

	nx = b->rc->px - b->rc->pdx;
	ny = b->rc->py - b->rc->pdy;
	if (!hit(b, nx, ny))
	{
		b->rc->px = nx;
		b->rc->py = ny;
	}
	return (0);
}

int	rc_boot_move_left(t_brain *b)
{
	float	nx;
	float	ny;

	nx = b->rc->px + b->rc->pdy;
	ny = b->rc->py - b->rc->pdx;
	if (!hit(b, nx, ny))
	{
		b->rc->px = nx;
		b->rc->py = ny;
	}
	return (0);
}

int	rc_boot_move_right(t_brain *b)
{
	float	nx;
	float	ny;

	nx = b->rc->px - b->rc->pdy;
	ny = b->rc->py + b->rc->pdx;
	if (!hit(b, nx, ny))
	{
		b->rc->px = nx;
		b->rc->py = ny;
	}
	return (0);
}

int	rc_boot_turn_left(t_brain *b)
{
	b->rc->pa -= RC_TURN;
	rc_wrap_angle(b);
	rc_update_dir(b);
	return (0);
}

/*
--  int rc_boot_turn_right(t_brain *b) --
is at rc_boot_world.c
due to norminette limit
*/
