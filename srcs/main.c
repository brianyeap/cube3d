/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:46:56 by brian             #+#    #+#             */
/*   Updated: 2025/08/11 23:28:18 by brian            ###   ########.fr       */
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
	init_buff(new->ctx, &new->ctx->buff, new->ctx->width, new->ctx->height);
	init_keys(new);
	new->initialized = 1;
	return (new);
}

int	main(int argc, char **argv)
{
	t_type			*map;

	(void)argv;
	if (argc < 2 || argc > 3)
		exit_cube(NULL, "Invalid number of arguments\n\
	launch with ./Cub3D <map_file>\n", 0);
	if ((map = ft_getmap_config(argv[1])) == NULL)
		exit_cube(NULL, "Map Not Found\n", 0);
	return (0);
}
