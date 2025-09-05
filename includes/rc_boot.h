/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:21:51 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 19:06:50 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RC_BOOT_H
# define RC_BOOT_H

#define RC_TURN   0.1f
#define RC_SPEED  5.0f

typedef struct s_brain	t_brain;

// rc boot draw
void			put_px(t_brain *b, int x, int y, int color);
void			clear_img(t_brain *b);
void			draw_3d(t_brain *b);

// rc boot hook
int				rc_boot_loop(t_brain *b);
int				rc_boot_keydown(int key, t_brain *b);

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

// rc boot movement
void			rc_update_dir(t_brain *b);
void			rc_wrap_angle(t_brain *b);

int				rc_boot_key_up(t_brain *b);
int				rc_boot_key_down(t_brain *b);
int				rc_boot_turn_left(t_brain *b);
int				rc_boot_turn_right(t_brain *b);

#endif /* RC_BOOT_H */