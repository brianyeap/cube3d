/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:15 by brian             #+#    #+#             */
/*   Updated: 2025/09/15 21:31:24 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	get_grid(t_map *m, int x, int y)
{
	int			val;

	if (x >= 0 && y >= 0)
	{
		if (y < m->height && x < m->grid[y]->length)
		{
			val = m->grid[y]->line[x];
			return (val);
		}
	}
	return (-1);
}

t_fpoint	to_grid(int x, int y, t_map *m)
{
	t_fpoint	ret;

	ret.x = x / m->bloc_size;
	ret.y = y / m->bloc_size;
	return (ret);
}
