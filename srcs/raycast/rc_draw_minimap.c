/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:10 by jow               #+#    #+#             */
/*   Updated: 2025/09/25 17:50:25 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "rc_boot.h"

void draw_minimap(t_brain *b)
{
    int x;
    int y;
    int i;
    int j;
    int map_width = b->map->width;
    int map_height = b->map->height;
    int minimap_size = 180;
    int start_x = 10;
    int start_y = 10;

    // Calculate scale factors
    float scale_x = (float)minimap_size / (float)map_width;
    float scale_y = (float)minimap_size / (float)map_height;

    y = 0;
    while (y < map_height)
    {
        x = 0;
        while (x < map_width)
        {
            int cell = cell_at(b, x, y);
            int color;

            if (cell == 1 || cell == -1)
                color = 0x000000;
            else if (cell == 0)
                color = 0xFFFFFF;
            // else if (cell == -1)
            //     color = 0x757575;
            // Calculate scaled pixel positions
            int pixel_x_start = start_x + (int)(x * scale_x);
            int pixel_y_start = start_y + (int)(y * scale_y);
            int pixel_x_end = start_x + (int)((x + 1) * scale_x);
            int pixel_y_end = start_y + (int)((y + 1) * scale_y);

            // Draw the scaled cell
            i = pixel_x_start;
            while (i < pixel_x_end)
            {
                j = pixel_y_start;
                while (j < pixel_y_end)
                {
                    put_px(b, i, j, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}

void draw_miniplayer(t_brain *b)
{
    int minimap_size = 180;
    int start_x = 10;
    int start_y = 10;
    int map_width = b->map->width;
    int map_height = b->map->height;

    // Get player position in grid coordinates
    float player_grid_x = b->rc->px / (float)b->map->bloc_size;
    float player_grid_y = b->rc->py / (float)b->map->bloc_size;

    // Calculate player position on minimap
    int player_minimap_x = start_x + (int)((player_grid_x / map_width) * minimap_size);
    int player_minimap_y = start_y + (int)((player_grid_y / map_height) * minimap_size);

    // Draw player as a red pixel (or small cross for better visibility)
    put_px(b, player_minimap_x, player_minimap_y, 0xFF0000); // Red

    // Optional: Draw a small cross for better visibility
    if (player_minimap_x > start_x)
        put_px(b, player_minimap_x - 1, player_minimap_y, 0xFF0000);
    if (player_minimap_x < start_x + minimap_size - 1)
        put_px(b, player_minimap_x + 1, player_minimap_y, 0xFF0000);
    if (player_minimap_y > start_y)
        put_px(b, player_minimap_x, player_minimap_y - 1, 0xFF0000);
    if (player_minimap_y < start_y + minimap_size - 1)
        put_px(b, player_minimap_x, player_minimap_y + 1, 0xFF0000);
}

void rc_draw_minimap(t_brain *b)
{
    draw_minimap(b);
    draw_miniplayer(b);
}
