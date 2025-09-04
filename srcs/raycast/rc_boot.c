/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:07:48 by brian             #+#    #+#             */
/*   Updated: 2025/09/04 20:07:24 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// srcs/raycast/rc_boot.c
#include "cube3d.h"
#include <math.h>
#include <stdlib.h>

/*
  This module is self-contained:
  - Uses your ctx->mlx_ptr / win_ptr
  - Allocates its own MLX image (doesn't depend on your t_buff definition)
  - Renders a simple 8x8 test map so you see something on launch
  - Keys: W (13), S (1), A (0), D (2), ESC (53)
*/

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// macOS MLX event codes
#define EV_KEYDOWN 2
#define EV_DESTROY 17

// Window size (can be different from ctx->width/height)
#define RC_W 1024
#define RC_H 512

// Local/static state for the boot demo (doesn't pollute your structs)
static void *g_img = NULL;
static char *g_data = NULL;
static int   g_bpp = 0;
static int   g_stride = 0;
static int   g_endian = 0;

static float g_px = 200.0f;
static float g_py = 200.0f;
static float g_pa = 0.0f;     // angle
static float g_pdx = 5.0f;    // derived from angle
static float g_pdy = 0.0f;

static t_map  *g_world = NULL;   // set by rc_boot_attach_world(...)
static int     g_tile  = 64;     // will be set from b->map->bloc_size


void rc_boot_attach_world(t_brain *b) {
  if (!b || !b->map || !b->player) return;

  g_world = b->map;
  g_tile  = b->map->bloc_size;

  // sync player pose from your engine
  g_px = (float)b->player->position->x;
  g_py = (float)b->player->position->y;
  g_pa = (float)b->player->angle;

  g_pdx = cosf(g_pa) * 5.0f;
  g_pdy = sinf(g_pa) * 5.0f;
}


static inline int cell_at(int mx, int my) {
  if (!g_world) return 1; // treat unknown as solid
  if (my < 0 || my >= g_world->height) return 1;
  t_map_line *row = g_world->grid[my];
  if (!row) return 1;
  if (mx < 0 || mx >= row->length) return 1;
  return row->line[mx];
}

// adjust this if your encoding differs
static inline int is_blocking(int v) {
  return (v == 1); // walls are "1"; doors/sprites/etc are not blocking
}


static inline float distf(float ax, float ay, float bx, float by) {
  float dx = ax - bx, dy = ay - by;
  return sqrtf(dx*dx + dy*dy);
}

static inline void put_px(int x, int y, int color) {
  if (x < 0 || x >= RC_W || y < 0 || y >= RC_H) return;
  int i = y * g_stride + x * (g_bpp / 8);
  g_data[i+0] = color & 0xFF;
  g_data[i+1] = (color >> 8) & 0xFF;
  g_data[i+2] = (color >>16) & 0xFF;
}

static void clear_img(void) {
  for (int y = 0; y < RC_H; y++)
    for (int x = 0; x < RC_W; x++)
      put_px(x, y, 0x000000);
}

static int hit(float x, float y) {
  if (!g_world) return 1;
  int mx = (int)(x / (float)g_tile);
  int my = (int)(y / (float)g_tile);
  return is_blocking(cell_at(mx, my));
}


static float fixed_dist(float rx, float ry, float ray_ang) {
  float d = distf(g_px, g_py, rx, ry);
  return d * cosf(ray_ang - g_pa); // remove fisheye
}

static void draw_3d(void) {
  const float fov = (float)M_PI / 3.0f; // 60 deg
  float step  = fov / (float)RC_W;
  float start = g_pa - fov * 0.5f;

  for (int col = 0; col < RC_W; col++) {
    float ang = start + col * step;
    float rdx = cosf(ang);
    float rdy = sinf(ang);
    float rx = g_px, ry = g_py;
    int   steps = 0;

    while (!hit(rx, ry) && steps < 300) {
      rx += rdx;
      ry += rdy;
      steps++;
    }

    float d = fixed_dist(rx, ry, ang);
    if (d < 0.001f) d = 0.001f;
    float h = ((float)g_tile / d) * (RC_W * 0.5f);

    int sy = (int)((RC_H - h) * 0.5f);
    int ey = sy + (int)h;
    if (sy < 0) sy = 0;
    if (ey > RC_H) ey = RC_H;

    // simple blue wall
    for (int y = sy; y < ey; y++) put_px(col, y, 0x0000FF);
  }
}

/* -------------------- public hooks -------------------- */

int rc_boot_loop(t_brain *b) {
  (void)b; // not needed for now
  clear_img();
  draw_3d();
  mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr, g_img, 0, 0);
  return 0;
}

int rc_boot_keydown(int key, t_brain *b) {
  (void)b;

  // mac keycodes
  if (key == 53) exit(0); // ESC

  if (key == 13) { // W
    float nx = g_px + g_pdx, ny = g_py + g_pdy;
    if (!hit(nx, ny)) { g_px = nx; g_py = ny; }
  } else if (key == 1) { // S
    float nx = g_px - g_pdx, ny = g_py - g_pdy;
    if (!hit(nx, ny)) { g_px = nx; g_py = ny; }
  } else if (key == 0) { // A
    g_pa -= 0.1f;
    if (g_pa < 0) g_pa += 2.0f*(float)M_PI;
    g_pdx = cosf(g_pa) * 5.0f;
    g_pdy = sinf(g_pa) * 5.0f;
  } else if (key == 2) { // D
    g_pa += 0.1f;
    if (g_pa > 2.0f*(float)M_PI) g_pa -= 2.0f*(float)M_PI;
    g_pdx = cosf(g_pa) * 5.0f;
    g_pdy = sinf(g_pa) * 5.0f;
  }
  return 0;
}

static int rc_boot_close(void *unused) {
  (void)unused;
  exit(0);
  return 0;
}

/*
  Call this ONCE after you create the window.
  It wires up the loop + key hooks and allocates the image.
*/
int rc_boot_init(t_brain *b) {
  if (!b || !b->ctx || !b->ctx->mlx_ptr || !b->ctx->win_ptr)
    return -1;

  g_img = mlx_new_image(b->ctx->mlx_ptr, RC_W, RC_H);
  if (!g_img) return -1;

  g_data = mlx_get_data_addr(g_img, &g_bpp, &g_stride, &g_endian);

  // angle must be set before dx/dy
  g_pa = 0.0f;
  g_pdx = cosf(g_pa) * 5.0f;
  g_pdy = sinf(g_pa) * 5.0f;

  // Register hooks (macOS)
//   mlx_loop_hook(b->ctx->mlx_ptr, rc_boot_loop, b);
//   mlx_hook(b->ctx->win_ptr, EV_DESTROY, 0, rc_boot_close, NULL);
//   mlx_hook(b->ctx->win_ptr, EV_KEYDOWN, 1L<<0, rc_boot_keydown, b);

  return 0;
}
