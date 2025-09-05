// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   rc_boot.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/02 20:07:48 by brian             #+#    #+#             */
// /*   Updated: 2025/09/05 14:20:36 by brian            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // srcs/raycast/rc_boot.c
// #include "cube3d.h"
// #include <math.h>
// #include <stdlib.h>

// void rc_boot_attach_world(t_brain *b) {
//   if (!b || !b->map || !b->player || !b->rc) return;
//   b->rc->world = b->map;
//   b->rc->tile  = b->map->bloc_size;
//   b->rc->px    = (float)b->player->position->x;
//   b->rc->py    = (float)b->player->position->y;
//   b->rc->pa    = (float)b->player->angle;
//   b->rc->pdx   = cosf(b->rc->pa) * 5.0f;
//   b->rc->pdy   = sinf(b->rc->pa) * 5.0f;
// }

// static inline int cell_at(t_brain *b, int mx, int my) {
//   if (!b || !b->rc || !b->rc->world) return 1;
//   t_map *w = b->rc->world;
//   if (my < 0 || my >= w->height) return 1;
//   t_map_line *row = w->grid[my];
//   if (!row) return 1;
//   if (mx < 0 || mx >= row->length) return 1;
//   return row->line[mx];
// }

// static inline int is_blocking(int v) { return (v == 1); }

// static inline float distf(float ax, float ay, float bx, float by) {
//   float dx = ax - bx, dy = ay - by;
//   return sqrtf(dx*dx + dy*dy);
// }

// static inline void put_px(t_brain *b, int x, int y, int color) {
//   if (!b || !b->rc) return;
//   if (x < 0 || x >= b->rc->w || y < 0 || y >= b->rc->h) return;
//   int i = y * b->rc->stride + x * (b->rc->bpp / 8);
//   b->rc->data[i+0] = color & 0xFF;
//   b->rc->data[i+1] = (color >> 8) & 0xFF;
//   b->rc->data[i+2] = (color >>16) & 0xFF;
// }

// static void clear_img(t_brain *b) {
//   for (int y = 0; y < b->rc->h; y++)
//     for (int x = 0; x < b->rc->w; x++)
//       put_px(b, x, y, 0x000000);
// }

// static int hit(t_brain *b, float x, float y) {
//   if (!b || !b->rc) return 1;
//   int mx = (int)(x / (float)b->rc->tile);
//   int my = (int)(y / (float)b->rc->tile);
//   return is_blocking(cell_at(b, mx, my));
// }

// static float fixed_dist(t_brain *b, float rx, float ry, float ray_ang) {
//   float d = distf(b->rc->px, b->rc->py, rx, ry);
//   return d * cosf(ray_ang - b->rc->pa); // remove fisheye
// }

// static void draw_3d(t_brain *b) {
//   const float fov = (float)M_PI / 3.0f; // 60 deg
//   float step  = fov / (float)b->rc->w;
//   float start = b->rc->pa - fov * 0.5f;

//   for (int col = 0; col < b->rc->w; col++) {
//     float ang = start + col * step;
//     float rdx = cosf(ang), rdy = sinf(ang);
//     float rx = b->rc->px, ry = b->rc->py;
//     int   steps = 0;

//     while (!hit(b, rx, ry) && steps < 300) { rx += rdx; ry += rdy; steps++; }

//     float d = fixed_dist(b, rx, ry, ang);
//     if (d < 0.001f) d = 0.001f;

//     float h = ((float)b->rc->tile / d) * (b->rc->w * 0.5f);

//     int sy = (int)((b->rc->h - h) * 0.5f);
//     int ey = sy + (int)h;
//     if (sy < 0) sy = 0;
//     if (ey > b->rc->h) ey = b->rc->h;

//     for (int y = sy; y < ey; y++) put_px(b, col, y, 0x0000FF);
//   }
// }

// /* -------------------- public hooks -------------------- */

// int rc_boot_loop(t_brain *b) {
//   clear_img(b);
//   draw_3d(b);
//   mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr, b->rc->img, 0, 0);
//   return 0;
// }

// int rc_boot_keydown(int key, t_brain *b) {
//   if (key == 53) exit(0);
//   if (key == 13) { // W
//     float nx = b->rc->px + b->rc->pdx, ny = b->rc->py + b->rc->pdy;
//     if (!hit(b, nx, ny)) { b->rc->px = nx; b->rc->py = ny; }
//   } else if (key == 1) { // S
//     float nx = b->rc->px - b->rc->pdx, ny = b->rc->py - b->rc->pdy;
//     if (!hit(b, nx, ny)) { b->rc->px = nx; b->rc->py = ny; }
//   } else if (key == 0) { // A
//     b->rc->pa -= 0.1f; if (b->rc->pa < 0) b->rc->pa += 2.0f*(float)M_PI;
//     b->rc->pdx = cosf(b->rc->pa) * 5.0f; b->rc->pdy = sinf(b->rc->pa) * 5.0f;
//   } else if (key == 2) { // D
//     b->rc->pa += 0.1f; if (b->rc->pa > 2.0f*(float)M_PI) b->rc->pa -= 2.0f*(float)M_PI;
//     b->rc->pdx = cosf(b->rc->pa) * 5.0f; b->rc->pdy = sinf(b->rc->pa) * 5.0f;
//   }
//   return 0;
// }



// static int rc_boot_close(void *unused) {
//   (void)unused;
//   exit(0);
//   return 0;
// }

// /*
//   Call this ONCE after you create the window.
//   It wires up the loop + key hooks and allocates the image.
// */
// int rc_boot_init(t_brain *b) {
//   if (!b || !b->ctx || !b->ctx->mlx_ptr || !b->ctx->win_ptr) return -1;

//   b->rc = malloc(sizeof(*b->rc));
//   if (!b->rc) return -1;

//   b->rc->w = 1024;
//   b->rc->h = 512;

//   b->rc->img = mlx_new_image(b->ctx->mlx_ptr, b->rc->w, b->rc->h);
//   if (!b->rc->img) { free(b->rc); b->rc = NULL; return -1; }

//   b->rc->data = mlx_get_data_addr(b->rc->img, &b->rc->bpp, &b->rc->stride, &b->rc->endian);

//   b->rc->pa = 0.0f;
//   b->rc->pdx = cosf(b->rc->pa) * 5.0f;
//   b->rc->pdy = sinf(b->rc->pa) * 5.0f;
//   b->rc->tile = 64;
//   b->rc->world = NULL;
//   return 0;
// }
