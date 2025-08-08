/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:46:56 by brian             #+#    #+#             */
/*   Updated: 2025/08/08 23:11:06 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_type			*map;

	(void)argv;
	if (argc < 2 || argc > 3)
		exit_cube(NULL, "Invalid number of arguments\n\
	launch with ./Cub3D <map_file>\n", 0);
	if ((map = ft_getmap_config(argv[1])) == NULL)
		exit_cube(NULL, "Map Not Found", 0);
	return (0);
}
