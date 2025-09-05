/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:26:36 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 14:50:09 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"


int rc_boot_loop(t_brain *b) {
  clear_img(b);
  draw_3d(b);
  mlx_put_image_to_window(b->ctx->mlx_ptr, b->ctx->win_ptr, b->rc->img, 0, 0);
  return 0;
}

int rc_boot_keydown(int key, t_brain *b) {
  if (key == 53) exit(0);
  if (key == 13) { // W
    float nx = b->rc->px + b->rc->pdx, ny = b->rc->py + b->rc->pdy;
    if (!hit(b, nx, ny)) { b->rc->px = nx; b->rc->py = ny; }
  } else if (key == 1) { // S
    float nx = b->rc->px - b->rc->pdx, ny = b->rc->py - b->rc->pdy;
    if (!hit(b, nx, ny)) { b->rc->px = nx; b->rc->py = ny; }
  } else if (key == 0) { // A
    b->rc->pa -= 0.1f; if (b->rc->pa < 0) b->rc->pa += 2.0f*(float)M_PI;
    b->rc->pdx = cosf(b->rc->pa) * 5.0f; b->rc->pdy = sinf(b->rc->pa) * 5.0f;
  } else if (key == 2) { // D
    b->rc->pa += 0.1f; if (b->rc->pa > 2.0f*(float)M_PI) b->rc->pa -= 2.0f*(float)M_PI;
    b->rc->pdx = cosf(b->rc->pa) * 5.0f; b->rc->pdy = sinf(b->rc->pa) * 5.0f;
  }
  return 0;
}

int rc_boot_close(void *unused) {
  (void)unused;
  exit(0);
  return 0;
}