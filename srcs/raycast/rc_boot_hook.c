/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:26:36 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 19:06:17 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

int	rc_boot_loop(t_brain *b)
{
	clear_img(b);
	draw_3d(b);
	mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr, b->rc->img, 0, 0);
	return (0);
}

void	rc_update_dir(t_brain *b)
{
	b->rc->pdx = cosf(b->rc->pa) * RC_SPEED;
	b->rc->pdy = sinf(b->rc->pa) * RC_SPEED;
}

void	rc_wrap_angle(t_brain *b)
{
	if (b->rc->pa < 0.0f)
		b->rc->pa += 2.0f * (float)M_PI;
	else if (b->rc->pa > 2.0f * (float)M_PI)
		b->rc->pa -= 2.0f * (float)M_PI;
}

int	rc_boot_keydown(int key, t_brain *b)
{
	if (key == KEY_ESC)
		exit_cube(b, "Exit From ESC", 0);
	else if (key == KEY_UP)
		return (rc_boot_key_up(b));
	else if (key == KEY_DOWN)
		return (rc_boot_key_down(b));
	else if (key == KEY_LEFT)
		return (rc_boot_turn_left(b));
	else if (key == KEY_RIGHT)
		return (rc_boot_turn_right(b));
	return (0);
}