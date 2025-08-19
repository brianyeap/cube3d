/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:01:11 by brian             #+#    #+#             */
/*   Updated: 2025/08/18 19:15:29 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_texture(t_brain *b, char *path, t_buff **t)
{
	ft_printf(CYAN"	-> %s", path);
	*t = malloc(sizeof(t_buff));
	if (*t)
	{
		(*t)->initialized = 1;
		(*t)->img = mlx_xpm_file_to_image(b->ctx->mlx_ptr, path,
				&(*t)->width, &(*t)->height);
		if (!(*t)->img)
			exit_cube(NULL, path, 0);
		(*t)->initialized = 2;
		(*t)->addr = mlx_get_data_addr((*t)->img, &(*t)->bits_per_pixel,
				&(*t)->line_length,
				&(*t)->endian);
		(*t)->max_addr = (*t)->line_length * (*t)->height;
		(*t)->offset = (*t)->bits_per_pixel / 8;
		(*t)->ratio = (*t)->width / b->map->bloc_size;
		(*t)->initialized = 3;
		ft_printf(GRN" - OK\n"RST);
	}
	else
		exit_cube(NULL, "Failed to malloc texture", 0);
}
