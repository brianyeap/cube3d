/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:10:27 by jow               #+#    #+#             */
/*   Updated: 2025/09/24 13:13:16 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./MiniLib/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>

// Key codes for Mac
#define KEY_ESC 53
#define KEY_UP 13
#define KEY_DOWN 1
#define KEY_LEFT 0
#define KEY_RIGHT 2

#define HEIGHT 512
#define WIDTH 1024

#define DEBUG 1 // Set to 1 for 2D debugging, 0 for 3D rendering

typedef struct s_dda
{
    /* Frame-constant values */
    double TILE;
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
} t_dda;

typedef struct s_brain
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;

    char *data;
    int bpp;
    int size_line;
    int endian;

    int player_x;
    int player_y;
    float player_dx;
    float player_dy;
    float player_angle;
    int map[64]; // 8x8 map

    void *wall_texture;
    char *wall_data;
    int wall_width;
    int wall_height;
    int wall_bpp;
    int wall_size_line;
    int wall_endian;
    t_dda dda;
} t_brain;

void draw_map(t_brain *brain);
void draw_square(int x, int y, int size, int colour, t_brain *brain);
int touch(float x, float y, t_brain *brain);

float calcDist(const float ax, const float ay, const float bx, const float by)
{
    return (sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
}

int close_window(void *param)
{
    exit(0);
    return (0);
}

int on_keypress(int keycode, void *param)
{
    t_brain *brain = (t_brain *)param;
    float new_x;
    float new_y;

    if (keycode == KEY_ESC)
        exit(0);
    else if (keycode == KEY_UP)
    {
        new_x = brain->player_x + brain->player_dx;
        new_y = brain->player_y + brain->player_dy;
        if (!touch(new_x, new_y, brain))
        {
            brain->player_x = new_x;
            brain->player_y = new_y;
        }
    }
    else if (keycode == KEY_DOWN)
    {
        new_x = brain->player_x - brain->player_dx;
        new_y = brain->player_y - brain->player_dy;
        if (!touch(new_x, new_y, brain))
        {
            brain->player_x = new_x;
            brain->player_y = new_y;
        }
    }
    else if (keycode == KEY_LEFT)
    {
        brain->player_angle -= 0.1;
        if (brain->player_angle < 0)
            brain->player_angle += 2 * M_PI;
        brain->player_dx = cos(brain->player_angle) * 5;
        brain->player_dy = sin(brain->player_angle) * 5;
    }
    else if (keycode == KEY_RIGHT)
    {
        brain->player_angle += 0.1;
        if (brain->player_angle > 2 * M_PI)
            brain->player_angle -= 2 * M_PI;
        brain->player_dx = cos(brain->player_angle) * 5;
        brain->player_dy = sin(brain->player_angle) * 5;
    }
    return (0);
}

/*-----------------------------------------------------------------------------------------------*/

void ft_put_pixel(int x, int y, int color, t_brain *brain)
{
    int index;

    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;
    if (x == 0 && y == 0)
        printf("ft_put_pixel called for (0,0) color: 0x%X\n", color);

    index = (y * brain->size_line) + (x * (brain->bpp / 8));

    if (brain->endian == 1) // Big endian: MSB first (ARGB)
    {
        brain->data[index + 0] = (color >> 24) & 0xFF; // A
        brain->data[index + 1] = (color >> 16) & 0xFF; // R
        brain->data[index + 2] = (color >> 8) & 0xFF;  // G
        brain->data[index + 3] = (color) & 0xFF;       // B
    }
    else // Little endian: LSB first (BGRA in memory)
    {
        brain->data[index + 0] = (color) & 0xFF;       // B
        brain->data[index + 1] = (color >> 8) & 0xFF;  // G
        brain->data[index + 2] = (color >> 16) & 0xFF; // R
        brain->data[index + 3] = (color >> 24) & 0xFF; // A
    }
}

void draw_square(int x, int y, int size, int colour, t_brain *brain)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            ft_put_pixel(x + i, y + j, colour, brain);
        }
    }
}

void draw_map(t_brain *brain)
{
    int x;
    int y;

    y = 0;
    printf("Drawing map...\n");
    while (y < 8)
    {
        x = 0;
        while (x < 8)
        {
            if (brain->map[y * 8 + x] == 1)
                draw_square(x * 20, y * 20, 20, 0x000000, brain); // Red wall
            else
                draw_square(x * 20, y * 20, 20, 0xFFFFFF, brain); // Gray floor
            x++;
        }
        y++;
    }
}

void ft_clear_image(t_brain *brain)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_put_pixel(x, y, 0, brain);
            x++;
        }
        y++;
    }
}

// check if ray touches wall
int touch(float x, float y, t_brain *brain)
{
    int map_x = (int)(x / 64);
    int map_y = (int)(y / 64);

    if (map_x < 0 || map_x >= 8 || map_y < 0 || map_y >= 8)
        return (1); // Hit boundary

    return (brain->map[map_y * 8 + map_x] == 1); // Hit wall
}

// corrected distance calculation
float fixed_dist(float player_x, float player_y, float ray_x, float ray_y, float ray_angle, t_brain *brain)
{
    float dist = calcDist(player_x, player_y, ray_x, ray_y);
    return (dist * cos(ray_angle - brain->player_angle)); // Fix fisheye effect
}

int get_texture_pixel(t_brain *brain, int tex_x, int tex_y)
{
    if (!brain->wall_data || tex_x < 0 || tex_x >= brain->wall_width ||
        tex_y < 0 || tex_y >= brain->wall_height)
        return 0xFFFFFF;
    int bytes = brain->wall_bpp / 8;
    if (bytes < 3)
        return 0xFFFFFF;
    int index = tex_y * brain->wall_size_line + tex_x * bytes;
    unsigned char b = (unsigned char)brain->wall_data[index + 0];
    unsigned char g = (unsigned char)brain->wall_data[index + 1];
    unsigned char r = (unsigned char)brain->wall_data[index + 2];
    return (r << 16) | (g << 8) | b; // 0xRRGGBB
}

void perform_dda(t_brain *brain)
{
    t_dda *dda = &brain->dda;

    if (dda->sideDistX < dda->sideDistY)
    {
        dda->sideDistX += dda->deltaDistX;
        dda->mapX += dda->stepX;
        dda->side = 0;
    }
    else
    {
        dda->sideDistY += dda->deltaDistY;
        dda->mapY += dda->stepY;
        dda->side = 1;
    }
    // out of bounds check
    if (dda->mapX < 0 || dda->mapX >= 8 || dda->mapY < 0 || dda->mapY >= 8)
    {
        dda->outOfBounds = 1;
        dda->hit = 1;
    }
    // ray hit wall check
    else if (brain->map[dda->mapY * 8 + dda->mapX] > 0)
        dda->hit = 1;
}

void calculate_step(t_brain *brain)
{
    t_dda *dda = &brain->dda;

    if (dda->rayDirX < 0)
    {
        dda->stepX = -1;
        dda->sideDistX = (dda->posX - dda->mapX) * dda->deltaDistX;
    }
    else
    {
        dda->stepX = 1;
        dda->sideDistX = (dda->mapX + 1.0 - dda->posX) * dda->deltaDistX;
    }
    if (dda->rayDirY < 0)
    {
        dda->stepY = -1;
        dda->sideDistY = (dda->posY - dda->mapY) * dda->deltaDistY;
    }
    else
    {
        dda->stepY = 1;
        dda->sideDistY = (dda->mapY + 1.0 - dda->posY) * dda->deltaDistY;
    }
}

void ray_setup(t_brain *brain, int x)
{
    t_dda *dda = &brain->dda;
    dda->cameraX = 2.0 * x / (double)WIDTH - 1.0;
    dda->rayDirX = dda->dirX + dda->planeX * dda->cameraX;
    dda->rayDirY = dda->dirY + dda->planeY * dda->cameraX;
    dda->mapX = (int)dda->posX;
    dda->mapY = (int)dda->posY;
    if (dda->rayDirX == 0.0)
        dda->deltaDistX = 1e30;
    else
        dda->deltaDistX = fabs(1.0 / dda->rayDirX);
    if (dda->rayDirY == 0.0)
        dda->deltaDistY = 1e30;
    else
        dda->deltaDistY = fabs(1.0 / dda->rayDirY);
}

static void init_dda(t_brain *brain)
{
    t_dda *dda = &brain->dda;
    dda->TILE = 64.0;
    dda->fov = M_PI / 3.0; // 60 deg
    dda->posX = brain->player_x / dda->TILE;
    dda->posY = brain->player_y / dda->TILE;
    dda->dirX = cos(brain->player_angle);
    dda->dirY = sin(brain->player_angle);
    dda->planeLen = tan(dda->fov / 2.0); // half of plane width
    dda->planeX = -dda->dirY * dda->planeLen;
    dda->planeY = dda->dirX * dda->planeLen;
}

void draw_line(t_brain *brain)
{
    t_dda *dda = &brain->dda;
    int safety;

    init_dda(brain);
    for (int x = 0; x < WIDTH; x++)
    {
        ray_setup(brain, x);
        calculate_step(brain);
        dda->hit = 0;
        dda->outOfBounds = 0;
        safety = 0;
        while (!dda->hit && safety++ < 2048)
            perform_dda(brain);
        if (dda->outOfBounds)
        {
            // printf("Ray out of bounds at column %d\n", x);
            // int mid = HEIGHT / 2;
            // for (int y = 0; y < mid; y++)
            //     ft_put_pixel(x, y, 0x87CEEB, brain);
            // for (int y = mid; y < HEIGHT; y++)
            //     ft_put_pixel(x, y, 0x2E2E2E, brain);
            continue;
        }
        // calculate perpendicular wall distance
        if (dda->side == 0)
        {
            double denom;
            if (dda->rayDirX == 0.0)
                denom = 1e-9;
            else
                denom = dda->rayDirX;
            dda->perpWallDist = (dda->mapX - dda->posX + (1 - dda->stepX) / 2.0) / denom;
        }
        else
        {
            double denom;
            if (dda->rayDirY == 0.0)
                denom = 1e-9;
            else
                denom = dda->rayDirY;
            dda->perpWallDist = (dda->mapY - dda->posY + (1 - dda->stepY) / 2.0) / denom;
        }
        if (dda->perpWallDist < 1e-6)
            dda->perpWallDist = 1e-6;
        dda->lineHeight = (int)(HEIGHT / dda->perpWallDist);
        if (dda->lineHeight < 1)
            dda->lineHeight = 1;
        dda->drawStart0 = (int)(HEIGHT / 2 - dda->lineHeight / 2);
        dda->drawEnd0 = dda->drawStart0 + dda->lineHeight;
        if (dda->drawStart0 < 0)
            dda->drawStart = 0;
        else
            dda->drawStart = dda->drawStart0;
        if (dda->drawEnd0 > HEIGHT)
            dda->drawEnd = HEIGHT;
        else
            dda->drawEnd = dda->drawEnd0;
        if (dda->side == 0)
            dda->wallX = dda->posY + dda->perpWallDist * dda->rayDirY;
        else
            dda->wallX = dda->posX + dda->perpWallDist * dda->rayDirX;
        dda->wallX -= floor(dda->wallX);
        dda->texX = (int)(dda->wallX * (double)brain->wall_width);
        if (dda->side == 0 && dda->rayDirX < 0)
            dda->texX = brain->wall_width - dda->texX - 1;
        if (dda->side == 1 && dda->rayDirY > 0)
            dda->texX = brain->wall_width - dda->texX - 1;
        if (dda->texX < 0)
            dda->texX = 0;
        if (dda->texX >= brain->wall_width)
            dda->texX = brain->wall_width - 1;
        // fill sky
        int y = 0;
        while (y < dda->drawStart)
            ft_put_pixel(x, y++, 0x87CEEB, brain);
        dda->step = (double)brain->wall_height / (double)dda->lineHeight;
        dda->texPos = (double)(dda->drawStart - dda->drawStart0) * dda->step;
        y = dda->drawStart;
        while (y < dda->drawEnd)
        {
            int texY = (int)dda->texPos;
            int color = get_texture_pixel(brain, dda->texX, texY);
            ft_put_pixel(x, y, color, brain);
            dda->texPos += dda->step;
            y++;
        }
        // fill floor
        y = dda->drawEnd;
        while (y < HEIGHT)
            ft_put_pixel(x, y++, 0x2E2E2E, brain);
        if (DEBUG)
        {
            int rx = dda->mapX * (int)dda->TILE + (int)dda->TILE / 2;
            int ry = dda->mapY * (int)dda->TILE + (int)dda->TILE / 2;
            ft_put_pixel(rx, ry, 0xFF0000, brain);
        }
    }
}

int draw_loop(t_brain *brain)
{
    ft_clear_image(brain);

    draw_line(brain); // This handles both 2D and 3D rendering based on DEBUG flag
    if (DEBUG)
    {
        draw_map(brain); // Show 2D map in debug mode
        // Draw player on minimap (scaled)
        draw_square((int)((brain->player_x / 64.0) * 20), (int)((brain->player_y / 64.0) * 20), 8, 0x00FF00, brain);
    }
    mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, brain->img_ptr, 0, 0);
    return (0);
}

void init_game(t_brain *brain)
{
    brain->mlx_ptr = mlx_init();
    brain->win_ptr = mlx_new_window(brain->mlx_ptr, WIDTH, HEIGHT, "Cube3D Test");
    brain->img_ptr = mlx_new_image(brain->mlx_ptr, WIDTH, HEIGHT);
    brain->data = mlx_get_data_addr(brain->img_ptr, &brain->bpp, &brain->size_line, &brain->endian);

    brain->wall_height = 64;
    brain->wall_width = 64;
    brain->wall_texture = mlx_xpm_file_to_image(brain->mlx_ptr, "wall-2.xpm", &brain->wall_width, &brain->wall_height);
    if (brain->wall_texture)
        brain->wall_data = mlx_get_data_addr(brain->wall_texture, &brain->wall_bpp, &brain->wall_size_line, &brain->wall_endian);
    else
        brain->wall_data = NULL;
    mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, brain->img_ptr, 0, 0);
}

int main(int ac, char **av)
{
    t_brain brain = (t_brain){0};
    int map_data[64] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1};

    init_game(&brain);

    brain.player_x = 200;
    brain.player_y = 200;
    brain.player_angle = 0;
    brain.player_dx = cos(brain.player_angle) * 5;
    brain.player_dy = sin(brain.player_angle) * 5;

    // Copy map data to the struct
    for (int i = 0; i < 64; i++)
        brain.map[i] = map_data[i];

    // drawMap(&brain);    // Draw the map
    // drawRays(&brain);   // Draw rays first (behind player)
    // drawPlayer(&brain); // Draw player at the center
    // drawPlayerDirection(&brain);
    mlx_loop_hook(brain.mlx_ptr, draw_loop, &brain);                       // Show which way player is facing
    mlx_hook(brain.win_ptr, 17, 0, close_window, NULL);                    // Hook Close Button
    mlx_hook(brain.win_ptr, KeyPress, KeyPressMask, &on_keypress, &brain); // Hook key press with X11 constants
    mlx_loop(brain.mlx_ptr);                                               // Event Loop

    return (0);
}