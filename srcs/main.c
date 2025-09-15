/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:46:56 by brian             #+#    #+#             */
/*   Updated: 2025/09/15 21:27:07 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_brain	*new_brain(int width, int height, char *name)
{
	t_brain	*new;

	new = malloc(sizeof(t_brain));
	new->ctx = new_ctx(width, height);
	new->ctx->win_ptr = mlx_new_window(new->ctx->mlx_ptr, width, height, name);
	new->map = NULL;
	new->player = NULL;
	new->rc = NULL;
	init_keys(new); // -init 10 keys
	new->initialized = 1;
	if (rc_boot_init(new) != 0)
		exit_cube(new, "\n\nError\nBoot renderer failed to init", 1);
	return (new);
}

int	loop_hook(t_brain *b)
{
	mlx_clear_window(b->ctx->mlx_ptr, b->ctx->win_ptr);
	key_press(-1, b);  // -handle continuous press and transmit to rc_boot_keydown

	rc_boot_loop(b); // -main drawing loop
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
	mlx_hook(b->ctx->win_ptr, 2, (1L << 0), &key_press, b); // -2 is for keypress event, update key pressed 0 is KeyPressMask
	mlx_hook(b->ctx->win_ptr, 17, (1L << 16), &red_x_exit, b); // 17 is destroy notify event (1L << 16) is StructureNotifyMask
	mlx_key_hook(b->ctx->win_ptr, &key_release, b); // delete key pressed
	mlx_do_key_autorepeaton(b->ctx->mlx_ptr); // techincally don't need sinf we handle it ourselves
	mlx_loop(b->ctx->mlx_ptr); // this is the main loop that never ends
}

int	main(int argc, char **argv)
{
	t_brain			*b;
	t_type			*map;

	if (argc != 2)
		exit_cube(NULL, "\n\nError\nInvalid number of arguments\n\n\
launch with ./Cub3D <map_file>\n", 0);
    // Parse the .cub config header (R/NO/SO/WE/EA/F/C) and get target res
	map = ft_getmap_config(argv[1]);
	if (!map)
		exit_cube(NULL, "\n\nError\nMap Not Found\n", 0);
	// Create the app “brain” (window, ctx, rc boot buffer, keys)
	b = new_brain(map->res[0], map->res[1], "Cube3D");
	// save brain pointer for exit
	exit_cube(b, "Init Exit", 1);
	// Sync ctx dims with parsed resolution
	b->ctx->width = map->res[0];
	b->ctx->height = map->res[1];
	ft_printf("Opening Map ""%s\n", argv[1]);
	// Load map file: textures, player, grid, sizes
	open_map(b, argv[1], map);
	debug_print_map_pretty(b->map);
	// Wire the map/player into the raycast “boot” renderer
	rc_boot_attach_world(b);
	// Validate the map enclosure/holes/borders
	if (!check_map(b->map))
		exit_cube(b, "\n\nError\nBAD MAP", 0);
	init_loop(b);
	return (0);
}
