/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:03:22 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 19:04:39 by brian            ###   ########.fr       */
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

int	rc_boot_turn_left(t_brain *b)
{
	b->rc->pa -= RC_TURN;
	rc_wrap_angle(b);
	rc_update_dir(b);
	return (0);
}

int	rc_boot_turn_right(t_brain *b)
{
	b->rc->pa += RC_TURN;
	rc_wrap_angle(b);
	rc_update_dir(b);
	return (0);
}
