/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:21:51 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 14:55:20 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#ifndef RC_BOOT_H
# define RC_BOOT_H

// rc boot draw
void			put_px(t_brain *b, int x, int y, int color);
void			clear_img(t_brain *b);
void			draw_3d(t_brain *b);

// rc boot hook
int				rc_boot_loop(t_brain *b);
int				rc_boot_keydown(int key, t_brain *b);
int				rc_boot_close(void *unused);

// rc boot init
int				rc_boot_init(t_brain *b);
void			rc_boot_attach_world(t_brain *b);

// rc boot math
float			distf(float ax, float ay, float bx, float by);
float			fixed_dist(t_brain *b, float rx, float ry, float ray_ang);

// rc boot world
int				cell_at(t_brain *b, int mx, int my);
int				is_blocking(int v);
int				hit(t_brain *b, float x, float y);

#endif /* RC_BOOT_H */