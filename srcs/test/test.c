/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:10:27 by jow               #+#    #+#             */
/*   Updated: 2025/08/22 03:03:51 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./MiniLib/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>

// Key codes for Mac
#define KEY_ESC 53
#define KEY_UP 13
#define KEY_DOWN 1
#define KEY_LEFT 0
#define KEY_RIGHT 2

typedef struct s_brain
{
    void *mlx_ptr;
    void *win_ptr;
    int player_x;
    int player_y;
    int map[64]; // 8x8 map
} t_brain;

void drawMap(t_brain *brain)
{
    int x, y, xo, yo;
    int tile_size = 64; // Full tile size for positioning
    int mapS = 64; // Size of each tile in the map

    int full_map_size = 512
    void *grey = mlx_xpm_file_to_image(brain->mlx_ptr, "grey.xpm", &full_map_size, &full_map_size);
    mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, grey, 0, 0);
    
    
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            xo = x * tile_size; // Offset by 2 pixels for border
            yo = y * tile_size; // Offset by 2 pixels for border

            if (brain->map[y * 8 + x] == 1) // Wall
            {
                void *wall = mlx_xpm_file_to_image(brain->mlx_ptr, "White.xpm", &mapS, &mapS);
                mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, wall, xo, yo);
            }
            else // Floor
            {
                void *floor = mlx_xpm_file_to_image(brain->mlx_ptr, "black.xpm", &mapS, &mapS);
                mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, floor, xo, yo);
            }
        }
    }
}

void drawPlayer(t_brain *brain)
{
    int width, height = 1;
    void *player_IMG = mlx_xpm_file_to_image(brain->mlx_ptr, "./yellow.xpm", &width, &height);
    mlx_put_image_to_window(brain->mlx_ptr, brain->win_ptr, player_IMG, brain->player_x, brain->player_y);
}

int close_window(void *param)
{
    exit(0);
    return (0);
}

int on_keypress(int keycode, void *param)
{
    t_brain *brain = (t_brain *)param;

    if (keycode == KEY_ESC)
        exit(0);
    else if (keycode == KEY_UP)
        brain->player_y -= 10;
    else if (keycode == KEY_DOWN)
        brain->player_y += 10;
    else if (keycode == KEY_LEFT)
        brain->player_x -= 10;
    else if (keycode == KEY_RIGHT)
        brain->player_x += 10;

    drawMap(brain);
    drawPlayer(brain);

    printf("Key pressed: %d\n", keycode);
    return (0);
}

int main(int ac, char **av)
{
    t_brain brain;
    int map_data[64] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1};

    brain.mlx_ptr = mlx_init();
    brain.win_ptr = mlx_new_window(brain.mlx_ptr, 1024, 512, "Cube3D Test");
    brain.player_x = 200;
    brain.player_y = 200;

    // Copy map data to the struct
    for (int i = 0; i < 64; i++)
        brain.map[i] = map_data[i];

    drawMap(&brain);                                                       // Draw the map
    drawPlayer(&brain);                                                    // Draw player at the center
    mlx_hook(brain.win_ptr, 17, 0, close_window, NULL);                    // Hook Close Button
    mlx_hook(brain.win_ptr, KeyPress, KeyPressMask, &on_keypress, &brain); // Hook key press with X11 constants
    mlx_loop(brain.mlx_ptr);                                               // Event Loop

    return (0);
}