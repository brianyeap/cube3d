/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:28:21 by brian             #+#    #+#             */
/*   Updated: 2025/09/25 17:54:10 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	clean_up(t_brain *b)
{
	if (b)
	{
		free(b);
	}
}

void	exit_cube(t_brain *brain, char *msg, int exit_now)
{
	static t_brain	*b = NULL;

	if (b == NULL && brain != NULL)
	{
		b = brain;
		ft_putstr("Stored brain pointer\n");
	}
	if (exit_now)
		return ;
	ft_putstr(RED"\nCub3D Exit: ");
	ft_putstr(msg);
	ft_putstr(RST"\n");
	clean_up(b);
	ft_putstr(YELO"Clean Up OK\n"RST);
	ft_putstr(BLUE"Exit Done\n"RST);
	exit(0);
}

void	free_map_check(t_type *map)
{
	if (!map)
		return ;
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map);
}
