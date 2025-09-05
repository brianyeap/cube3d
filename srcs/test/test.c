/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:10:27 by jow               #+#    #+#             */
/*   Updated: 2025/09/06 00:24:57 by jow              ###   ########.fr       */
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
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int map_x;
    int map_y;
    int side; // 0 if NS wall hit, 1 if EW wall hit
    int hit;
    double perp_wall_dist;
    double wall_x; // exact position where wall was hit
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

/*
- Axes:
    x increases to the right
    y increases downwards
- Angles:
    > 0 radians
        - dx = cos(0) = 1
        - dy = sin(0) = 0
        - Facing right (east)
    > π/2 radians 90deg = down (south)
        - dx = cos(pi/2) = 0
        - dy = sin(pi/2) = 1
        - Facing down (south)
    > π radians 180deg = left (west)
        - dx = cos(pi) = -1
        - dy = sin(pi) = 0
        - Facing left (west)
    > 3π/2 radians 270deg = up (north)
        - dx = cos(3pi/2) = 0
        - dy = sin(3pi/2) = -1
        - Facing up (north)
- Why use cos and sin?
    - sin cos mapping uses the unit circle to turn an angle into a direction vector
*/

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
    // draw_map(brain);
    // draw_square(brain->player_x, brain->player_y, 10, 0xFF0000, brain);
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

// Add this helper function for corrected distance calculation
float fixed_dist(float player_x, float player_y, float ray_x, float ray_y, float ray_angle, t_brain *brain)
{
    float dist = calcDist(player_x, player_y, ray_x, ray_y);
    return (dist * cos(ray_angle - brain->player_angle)); // Fix fisheye effect
}

int get_texture_pixel(t_brain *brain, int tex_x, int tex_y)
{
    int index;
    int color;

    if (!brain->wall_data || tex_x < 0 || tex_x >= brain->wall_width ||
        tex_y < 0 || tex_y >= brain->wall_height)
        return (0xFFFFFF); // Return white if no texture or out of bounds

    index = (tex_y * brain->wall_size_line) + (tex_x * (brain->wall_bpp / 8));

    if (brain->wall_endian == 1) // Big endian
    {
        color = (brain->wall_data[index + 0] << 24) |
                (brain->wall_data[index + 1] << 16) |
                (brain->wall_data[index + 2] << 8) |
                (brain->wall_data[index + 3]);
    }
    else // Little endian
    {
        color = (brain->wall_data[index + 3] << 24) |
                (brain->wall_data[index + 2] << 16) |
                (brain->wall_data[index + 1] << 8) |
                (brain->wall_data[index + 0]);
    }

    return (color & 0xFFFFFF); // Remove alpha channel
}

void draw_line(t_brain *brain)
{
    float fov = M_PI / 3; // 60 degree field of view
    float angle_step = fov / WIDTH;
    float start_angle = brain->player_angle - fov / 2;
    int i;
    int steps;

    i = 0;
    while (i < WIDTH)
    {
        float ray_angle = start_angle + (i * angle_step);
        float ray_dx = cos(ray_angle);
        float ray_dy = sin(ray_angle);
        float ray_x = brain->player_x;
        float ray_y = brain->player_y;
        steps = 0;

        // Cast ray until it hits a wall
        while (!touch(ray_x, ray_y, brain) && steps < 1000)
        {
            if (DEBUG)
                ft_put_pixel((int)ray_x, (int)ray_y, 0xFF0000, brain);
            ray_x += ray_dx;
            ray_y += ray_dy;
            steps++;
        }

        if (!DEBUG)
        {
            // Calculate wall hit position
            float dist = fixed_dist(brain->player_x, brain->player_y, ray_x, ray_y, ray_angle, brain);
            float wall_height = (64.0 / dist) * (WIDTH / 2);
            int start_y = (HEIGHT - wall_height) / 2;
            int end_y = start_y + wall_height;

            // Calculate texture X coordinate
            float wall_hit_x = ray_x - floor(ray_x / 64) * 64; // Position within the 64x64 tile
            float wall_hit_y = ray_y - floor(ray_y / 64) * 64;

            // Determine which side of the wall was hit to get correct texture coordinate
            int tex_x;
            if (fabs(ray_dx) > fabs(ray_dy)) // Hit vertical wall
                tex_x = (int)(wall_hit_y * brain->wall_width / 64);
            else // Hit horizontal wall
                tex_x = (int)(wall_hit_x * brain->wall_width / 64);

            if (start_y < 0)
                start_y = 0;
            if (end_y > HEIGHT)
                end_y = HEIGHT;
            // Draw the textured wall column
            for (int y = start_y; y < end_y && y >= 0 && y < HEIGHT; y++)
            {
                // Calculate texture Y coordinate
                float tex_y_ratio = (float)(y - start_y) / wall_height;
                int tex_y = (int)(tex_y_ratio * brain->wall_height);

                // Get the color from texture
                int color = get_texture_pixel(brain, tex_x, tex_y);
                ft_put_pixel(i, y, color, brain);
            }
        }
        i++;
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
    brain->wall_texture = mlx_xpm_file_to_image(brain->mlx_ptr, "wall.xpm", &brain->wall_width, &brain->wall_height);
    brain->wall_data = mlx_get_data_addr(brain->wall_texture, &brain->wall_bpp, &brain->wall_size_line, &brain->wall_endian);
    mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, brain->img_ptr, 0, 0);
}

int main(int ac, char **av)
{
    t_brain brain;
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
    brain.player_dx = cos(brain.player_angle) * 5;
    brain.player_dy = sin(brain.player_angle) * 5;
    brain.player_angle = 0;

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