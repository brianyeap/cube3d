/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:46:56 by brian             #+#    #+#             */
/*   Updated: 2025/09/04 21:04:44 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_brain	*new_brain(int width, int height, char *name)
{
	t_brain	*new;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->ctx->color = 0x00FFFF;
	new->map = NULL;
	new->player = NULL;
	new->rc = NULL;
	init_buff(new->ctx, &new->ctx->buff, new->ctx->width, new->ctx->height);
	init_keys(new);
	new->initialized = 1;
	if (rc_boot_init(new) != 0)
		exit_cube(new, "Boot renderer failed to init", 1);
	return (new);
}

int	loop_hook(t_brain *b)
{
	mlx_clear_window(b->ctx->mlx_ptr, b->ctx->win_ptr);
	key_press(-1, b);

	rc_boot_loop(b);
	return (b->initialized);
}


int	red_x_exit(void *brain)
{
	exit_cube(brain, "Exit From Red Cross", 0);
	return (1);
}

void	init_loop(t_brain *b)
{
	ft_putstr("Loop Init OK\n");
	mlx_loop_hook(b->ctx->mlx_ptr, &loop_hook, b);
	mlx_hook(b->ctx->win_ptr, 2, (1L << 0), &key_press, b);
	mlx_hook(b->ctx->win_ptr, 17, (1L << 16), &red_x_exit, b);
	mlx_key_hook(b->ctx->win_ptr, &key_release, b);
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr);
	mlx_loop(b->ctx->mlx_ptr);
}

// Helpers: tweak these to match ft_str_to_int_tab’s encoding.
static char int_to_tile(int v)
{
    // Common conventions; adjust to your encoding
    if (v == -1) return ' ';      // void / outside
    if (v == 0)  return '.';      // floor/empty
    if (v == 1)  return '#';      // wall
    if (v == 2)  return '2';      // e.g., door/sprite/etc
    if (v == 3)  return '3';
    if (v == 4)  return '4';
    // fall back to digit or '?'
    if (v >= 0 && v <= 9) return (char)('0' + v);
    return '?';
}


void debug_print_map_pretty(t_map *m)
{
    if (!m || !m->grid) { ft_putstr("Map is NULL\n"); return; }

    ft_printf("Map %dx%d\n", m->width, m->height);
    for (int y = 0; y < m->height; y++)
    {
        t_map_line *row = m->grid[y];
        if (!row) { ft_putstr("(null row)\n"); continue; }

        for (int x = 0; x < row->length; x++)
            ft_putchar(int_to_tile(row->line[x]));
        ft_putchar('\n');
    }
}



int	main(int argc, char **argv)
{
	t_brain			*b;
	t_type			*map;

	if (argc != 2)
		exit_cube(NULL, "Invalid number of arguments\n\n\
launch with ./Cub3D <map_file>\n", 0);
	map = ft_getmap_config(argv[1]);
	if (!map)
		exit_cube(NULL, "Map Not Found\n", 0);
	b = new_brain(map->res[0], map->res[1], "Cube3D");
	exit_cube(b, "Init Exit", 1);
	b->ctx->width = map->res[0];
	b->ctx->height = map->res[1];
	ft_printf("Opening Map ""%s\n", argv[1]);
	open_map(b, argv[1], map);
	debug_print_map_pretty(b->map);
	rc_boot_attach_world(b);
	if (!check_map(b->map))
		exit_cube(b, "BAD MAP", 0);
	init_loop(b);
	return (0);
}
