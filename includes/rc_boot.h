/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:21:51 by brian             #+#    #+#             */
/*   Updated: 2025/09/24 00:20:30 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RC_BOOT_H
#define RC_BOOT_H

#define RC_TURN 0.03f
#define RC_SPEED 2.0f

typedef struct s_ray
{
    /* Frame-constant values */
    double map_area;
    double fov;
    double posX; /* player position in tiles */
    double posY;
    double dirX; /* normalized direction */
    double dirY;
    double planeLen; /* half-width of camera plane */
    double planeX;   /* camera plane vector */
    double planeY;
    /* Per-column (ray) values */
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    int side; /* 0 NS, 1 EW */
    int hit;
    int outOfBounds;
    double perpWallDist;
    int lineHeight;
    int drawStart0; // unclamped values
    int drawEnd0;
    int drawStart; // clamped values
    int drawEnd;
    double wallX;
    int texX;
    double step;
    double texPos;
} t_ray;

typedef struct s_brain t_brain;

// rc boot draw
void put_px(t_brain *b, int x, int y, int color);
void clear_img(t_brain *b);
void draw_3d(t_brain *b);

// rc boot hook
int rc_boot_loop(t_brain *b);
int rc_boot_keydown(int key, t_brain *b);

// rc boot init
int rc_boot_init(t_brain *b);
void rc_boot_attach_world(t_brain *b);

// rc boot math
float distf(float ax, float ay, float bx, float by);
float fixed_dist(float player_x, float player_y, float ray_x, float ray_y, float ray_angle, t_brain *b);

// rc boot world
int cell_at(t_brain *b, int mx, int my);
int is_blocking(int v);
int hit(t_brain *b, float x, float y);

// rc boot movement
void rc_update_dir(t_brain *b);
void rc_wrap_angle(t_brain *b);

int rc_boot_key_up(t_brain *b);
int rc_boot_key_down(t_brain *b);
int rc_boot_turn_left(t_brain *b);
int rc_boot_turn_right(t_brain *b);

#endif /* RC_BOOT_H */