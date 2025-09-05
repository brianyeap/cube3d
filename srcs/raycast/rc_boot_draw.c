/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:35 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 14:54:06 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void put_px(t_brain *b, int x, int y, int color)
{
    if (!b || !b->rc)
        return;
    if (x < 0 || x >= b->rc->w || y < 0 || y >= b->rc->h)
        return;
    int i = y * b->rc->stride + x * (b->rc->bpp / 8);
    b->rc->data[i + 0] = color & 0xFF;
    b->rc->data[i + 1] = (color >> 8) & 0xFF;
    b->rc->data[i + 2] = (color >> 16) & 0xFF;
}

void clear_img(t_brain *b) {
  for (int y = 0; y < b->rc->h; y++)
    for (int x = 0; x < b->rc->w; x++)
      put_px(b, x, y, 0x000000);
}

void draw_3d(t_brain *b) {
  const float fov = (float)M_PI / 3.0f; // 60 deg
  float step  = fov / (float)b->rc->w;
  float start = b->rc->pa - fov * 0.5f;

  for (int col = 0; col < b->rc->w; col++) {
    float ang = start + col * step;
    float rdx = cosf(ang), rdy = sinf(ang);
    float rx = b->rc->px, ry = b->rc->py;
    int   steps = 0;

    while (!hit(b, rx, ry) && steps < 300) { rx += rdx; ry += rdy; steps++; }

    float d = fixed_dist(b, rx, ry, ang);
    if (d < 0.001f) d = 0.001f;

    float h = ((float)b->rc->tile / d) * (b->rc->w * 0.5f);

    int sy = (int)((b->rc->h - h) * 0.5f);
    int ey = sy + (int)h;
    if (sy < 0) sy = 0;
    if (ey > b->rc->h) ey = b->rc->h;

    for (int y = sy; y < ey; y++) put_px(b, col, y, 0x0000FF);
  }
}