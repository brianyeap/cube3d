/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:10:27 by jow               #+#    #+#             */
/*   Updated: 2025/09/22 22:10:45 by jow              ###   ########.fr       */
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

#define DEBUG 0 // Set to 1 for 2D debugging, 0 for 3D rendering

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
    while (y < 8)
    {
        x = 0;
        while (x < 8)
        {
            if (brain->map[y * 8 + x] == 1)
                draw_square(x * 64, y * 64, 64, 0xFFFFFF, brain);
            else
                draw_square(x * 64, y * 64, 64, 0, brain);
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

    if (ray->sideDistX < ray->sideDistY)
    {
        ray->sideDistX += ray->deltaDistX;
        ray->mapX += ray->stepX;
        ray->side = 0;
    }
    else
    {
        ray->sideDistY += ray->deltaDistY;
        ray->mapY += ray->stepY;
        ray->side = 1;
    }
    // out of bounds check
    if (ray->mapX < 0 || ray->mapX >= 8 || ray->mapY < 0 || ray->mapY >= 8)
    {
        ray->outOfBounds = 1;
        ray->hit = 1;
    }
    // ray hit wall check
    else if (brain->map[ray->mapY * 8 + ray->mapX] > 0)
        ray->hit = 1;
}

void calculate_step(t_brain *brain)
{
    t_dda *dda = &brain->dda;

    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
    }
}

void ray_setup(t_brain *brain, int x)
{
    t_dda *dda = &brain->dda;
    ray->cameraX = 2.0 * x / (double)WIDTH - 1.0;
    ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
    ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
    ray->mapX = (int)ray->posX;
    ray->mapY = (int)ray->posY;
    if (ray->rayDirX == 0.0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1.0 / ray->rayDirX);
    if (ray->rayDirY == 0.0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1.0 / ray->rayDirY);
}

static void init_dda(t_brain *brain)
{
    t_dda *dda = &brain->dda;
    ray->TILE = 64.0;
    ray->fov = M_PI / 3.0; // 60 deg
    ray->posX = brain->player_x / ray->TILE;
    ray->posY = brain->player_y / ray->TILE;
    ray->dirX = cos(brain->player_angle);
    ray->dirY = sin(brain->player_angle);
    ray->planeLen = tan(ray->fov / 2.0); // half of plane width
    ray->planeX = -ray->dirY * ray->planeLen;
    ray->planeY = ray->dirX * ray->planeLen;
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
        ray->hit = 0;
        ray->outOfBounds = 0;
        safety = 0;
        while (!ray->hit && safety++ < 2048)
            perform_dda(brain);
        if (ray->outOfBounds)
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
        if (ray->side == 0)
        {
            double denom;
            if (ray->rayDirX == 0.0)
                denom = 1e-9;
            else
                denom = ray->rayDirX;
            ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2.0) / denom;
        }
        else
        {
            double denom;
            if (ray->rayDirY == 0.0)
                denom = 1e-9;
            else
                denom = ray->rayDirY;
            ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2.0) / denom;
        }
        if (ray->perpWallDist < 1e-6)
            ray->perpWallDist = 1e-6;
        ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
        if (ray->lineHeight < 1)
            ray->lineHeight = 1;
        ray->drawStart0 = (int)(HEIGHT / 2 - ray->lineHeight / 2);
        ray->drawEnd0 = ray->drawStart0 + ray->lineHeight;
        if (ray->drawStart0 < 0)
            ray->drawStart = 0;
        else
            ray->drawStart = ray->drawStart0;
        if (ray->drawEnd0 > HEIGHT)
            ray->drawEnd = HEIGHT;
        else
            ray->drawEnd = ray->drawEnd0;
        if (ray->side == 0)
            ray->wallX = ray->posY + ray->perpWallDist * ray->rayDirY;
        else
            ray->wallX = ray->posX + ray->perpWallDist * ray->rayDirX;
        ray->wallX -= floor(ray->wallX);
        ray->texX = (int)(ray->wallX * (double)brain->wall_width);
        if (ray->side == 0 && ray->rayDirX < 0)
            ray->texX = brain->wall_width - ray->texX - 1;
        if (ray->side == 1 && ray->rayDirY > 0)
            ray->texX = brain->wall_width - ray->texX - 1;
        if (ray->texX < 0)
            ray->texX = 0;
        if (ray->texX >= brain->wall_width)
            ray->texX = brain->wall_width - 1;
        // fill sky
        int y = 0;
        while (y < ray->drawStart)
            ft_put_pixel(x, y++, 0x87CEEB, brain);
        ray->step = (double)brain->wall_height / (double)ray->lineHeight;
        ray->texPos = (double)(ray->drawStart - ray->drawStart0) * ray->step;
        y = ray->drawStart;
        while (y < ray->drawEnd)
        {
            int texY = (int)ray->texPos;
            int color = get_texture_pixel(brain, ray->texX, texY);
            ft_put_pixel(x, y, color, brain);
            ray->texPos += ray->step;
            y++;
        }
        // fill floor
        y = ray->drawEnd;
        while (y < HEIGHT)
            ft_put_pixel(x, y++, 0x2E2E2E, brain);
        if (DEBUG)
        {
            int rx = ray->mapX * (int)ray->TILE + (int)ray->TILE / 2;
            int ry = ray->mapY * (int)ray->TILE + (int)ray->TILE / 2;
            ft_put_pixel(rx, ry, 0xFF0000, brain);
        }
    }
}

int draw_loop(t_brain *brain)
{
    ft_clear_image(brain);

    if (DEBUG)
    {
        draw_map(brain); // Show 2D map in debug mode
        draw_square(brain->player_x, brain->player_y, 10, 0xFF0000, brain);
    }
    draw_line(brain); // This handles both 2D and 3D rendering based on DEBUG flag
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