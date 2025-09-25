/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:35 by brian             #+#    #+#             */
/*   Updated: 2025/09/25 17:11:47 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void clear_img(t_brain *b)
{
    int y;
    int x;

    y = 0;
    while (y < b->rc->h)
    {
        x = 0;
        while (x < b->rc->w)
        {
            put_px(b, x, y, 0x000000);
            x++;
        }
        y++;
    }
}

int get_texture_pixel(t_brain *b, int tex_x, int tex_y)
{
    t_buff *tex = NULL;

    // Select wall texture based on ray side and direction
    if (b->ray->side == 0) // Vertical wall (east/west)
    {
        if (b->ray->rayDirX > 0)
            tex = b->map->w_e; // East wall
        else
            tex = b->map->w_w; // West wall
    }
    else // Horizontal wall (north/south)
    {
        if (b->ray->rayDirY > 0)
            tex = b->map->w_s; // South wall
        else
            tex = b->map->w_n; // North wall
    }

    if (!tex || tex_x < 0 || tex_x >= tex->width ||
        tex_y < 0 || tex_y >= tex->height)
        return 0xFFFFFF;
    int bytes = tex->offset;
    if (bytes < 3)
        return 0xFFFFFF;
    int index = tex_y * tex->line_length + tex_x * bytes;
    unsigned char *data = (unsigned char *)tex->addr;
    unsigned char b_ = data[index + 0];
    unsigned char g_ = data[index + 1];
    unsigned char r_ = data[index + 2];
    return (r_ << 16) | (g_ << 8) | b_; // 0xRRGGBB
}

void perform_dda(t_brain *b)
{
    if (b->ray->sideDistX < b->ray->sideDistY)
    {
        b->ray->sideDistX += b->ray->deltaDistX;
        b->ray->mapX += b->ray->stepX;
        b->ray->side = 0;
    }
    else
    {
        b->ray->sideDistY += b->ray->deltaDistY;
        b->ray->mapY += b->ray->stepY;
        b->ray->side = 1;
    }
    // out of bounds check
    if (b->ray->mapX < 0 || b->ray->mapX >= b->map->width || b->ray->mapY < 0 || b->ray->mapY >= b->map->height)
    {
        b->ray->outOfBounds = 1;
        b->ray->hit = 1;
    }
    // ray hit wall check - use cell_at for proper map lookup
    else if (cell_at(b, b->ray->mapX, b->ray->mapY) > 0)
        b->ray->hit = 1;
}

void calculate_step(t_brain *b)
{
    if (b->ray->rayDirX < 0)
    {
        b->ray->stepX = -1;
        b->ray->sideDistX = (b->ray->posX - b->ray->mapX) * b->ray->deltaDistX;
    }
    else
    {
        b->ray->stepX = 1;
        b->ray->sideDistX = (b->ray->mapX + 1.0 - b->ray->posX) * b->ray->deltaDistX;
    }
    if (b->ray->rayDirY < 0)
    {
        b->ray->stepY = -1;
        b->ray->sideDistY = (b->ray->posY - b->ray->mapY) * b->ray->deltaDistY;
    }
    else
    {
        b->ray->stepY = 1;
        b->ray->sideDistY = (b->ray->mapY + 1.0 - b->ray->posY) * b->ray->deltaDistY;
    }
}

void ray_setup(t_brain *b, int x)
{
    b->ray->cameraX = 2.0 * x / (double)WIN_W - 1.0;
    b->ray->rayDirX = b->ray->dirX + b->ray->planeX * b->ray->cameraX;
    b->ray->rayDirY = b->ray->dirY + b->ray->planeY * b->ray->cameraX;
    b->ray->mapX = (int)b->ray->posX;
    b->ray->mapY = (int)b->ray->posY;
    if (b->ray->rayDirX == 0.0)
        b->ray->deltaDistX = 1e30;
    else
        b->ray->deltaDistX = fabs(1.0 / b->ray->rayDirX);
    if (b->ray->rayDirY == 0.0)
        b->ray->deltaDistY = 1e30;
    else
        b->ray->deltaDistY = fabs(1.0 / b->ray->rayDirY);
}

void init_dda(t_brain *b)
{
    b->ray->fov = M_PI / 3.0; // 60 deg
    b->ray->posX = b->rc->px / (double)b->map->bloc_size;
    b->ray->posY = b->rc->py / (double)b->map->bloc_size;
    b->ray->dirX = cos(b->rc->pa);
    b->ray->dirY = sin(b->rc->pa);
    b->ray->planeLen = tan(b->ray->fov / 2.0); // half of plane width
    b->ray->planeX = -b->ray->dirY * b->ray->planeLen;
    b->ray->planeY = b->ray->dirX * b->ray->planeLen;
}

void draw_3d(t_brain *b)
{
    int safety;

    init_dda(b);
    for (int x = 0; x < WIN_W; x++)
    {
        ray_setup(b, x);
        calculate_step(b);
        b->ray->hit = 0;
        b->ray->outOfBounds = 0;
        safety = 0;
        while (!b->ray->hit && safety++ < 2048)
            perform_dda(b);
        if (b->ray->outOfBounds)
        {
            int mid = WIN_H / 2;
            for (int y = 0; y < mid; y++)
                put_px(b, x, y, 0x87CEEB);
            for (int y = mid; y < WIN_H; y++)
                put_px(b, x, y, 0x2E2E2E);
            continue;
        }
        // calculate perpendicular wall distance
        if (b->ray->side == 0)
        {
            double denom;
            if (b->ray->rayDirX == 0.0)
                denom = 1e-9;
            else
                denom = b->ray->rayDirX;
            b->ray->perpWallDist = (b->ray->mapX - b->ray->posX + (1 - b->ray->stepX) / 2.0) / denom;
        }
        else
        {
            double denom;
            if (b->ray->rayDirY == 0.0)
                denom = 1e-9;
            else
                denom = b->ray->rayDirY;
            b->ray->perpWallDist = (b->ray->mapY - b->ray->posY + (1 - b->ray->stepY) / 2.0) / denom;
        }
        if (b->ray->perpWallDist < 1e-6)
            b->ray->perpWallDist = 1e-6;
        b->ray->lineHeight = (int)(WIN_H / b->ray->perpWallDist);
        if (b->ray->lineHeight < 1)
            b->ray->lineHeight = 1;
        b->ray->drawStart0 = (int)(WIN_H / 2 - b->ray->lineHeight / 2);
        b->ray->drawEnd0 = b->ray->drawStart0 + b->ray->lineHeight;
        if (b->ray->drawStart0 < 0)
            b->ray->drawStart = 0;
        else
            b->ray->drawStart = b->ray->drawStart0;
        if (b->ray->drawEnd0 > WIN_H)
            b->ray->drawEnd = WIN_H;
        else
            b->ray->drawEnd = b->ray->drawEnd0;
        if (b->ray->side == 0)
            b->ray->wallX = b->ray->posY + b->ray->perpWallDist * b->ray->rayDirY;
        else
            b->ray->wallX = b->ray->posX + b->ray->perpWallDist * b->ray->rayDirX;
        b->ray->wallX -= floor(b->ray->wallX);
        b->ray->texX = (int)(b->ray->wallX * (double)b->rc->tile);
        if (b->ray->side == 0 && b->ray->rayDirX < 0)
            b->ray->texX = b->rc->tile - b->ray->texX - 1;
        if (b->ray->side == 1 && b->ray->rayDirY > 0)
            b->ray->texX = b->rc->tile - b->ray->texX - 1;
        if (b->ray->texX < 0)
            b->ray->texX = 0;
        if (b->ray->texX >= b->rc->tile)
            b->ray->texX = b->rc->tile - 1;
        // fill sky
        int y = 0;
        while (y < b->ray->drawStart)
            put_px(b, x, y++, b->map->c_rgb);
        b->ray->step = (double)b->rc->tile / (double)b->ray->lineHeight;
        b->ray->texPos = (double)(b->ray->drawStart - b->ray->drawStart0) * b->ray->step;
        y = b->ray->drawStart;
        while (y < b->ray->drawEnd)
        {
            int texY = (int)b->ray->texPos;
            int color = get_texture_pixel(b, b->ray->texX, texY);
            put_px(b, x, y, color);
            b->ray->texPos += b->ray->step;
            y++;
        }
        // fill floor
        y = b->ray->drawEnd;
        while (y < WIN_H)
            put_px(b, x, y++, b->map->f_rgb);
        // if (DEBUG)
        // {
        //     int rx = ray->mapX * (int)ray->TILE + (int)ray->TILE / 2;
        //     int ry = ray->mapY * (int)ray->TILE + (int)ray->TILE / 2;
        //     ft_put_pixel(rx, ry, 0xFF0000, brain);
        // }
    }
}