/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:47:16 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 18:26:20 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/debug.h"
#include "../../includes/map.h"

char	int_to_tile(int v)
{
	if (v == -1)
		return (' ');
	if (v == 0)
		return ('.');
	if (v == 1)
		return ('#');
	return ('?');
}

int	debug_check_map(t_map *m)
{
	if (!m || !m->grid)
	{
		ft_putstr("Map is NULL\n");
		return (0);
	}
	ft_printf("Map %dx%d\n", m->width, m->height);
	return (1);
}

void	debug_print_map_pretty(t_map *m)
{
	int			y;
	int			x;
	t_map_line	*row;

	if (!debug_check_map(m))
		return ;
	y = 0;
	while (y < m->height)
	{
		row = m->grid[y];
		if (!row)
		{
			ft_putstr("(null row)\n");
			y++;
			continue ;
		}
		x = 0;
		while (x < row->length)
		{
			ft_putchar(int_to_tile(row->line[x]));
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

