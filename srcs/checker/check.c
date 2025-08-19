/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:22:22 by brian             #+#    #+#             */
/*   Updated: 2025/08/18 02:23:53 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_surround(t_map *m, t_point *pos)
{
	int	cur;
	int	verif;

	cur = get_grid(m, pos->x, pos->y, 0);
	verif = get_grid(m, pos->x, pos->y - 1, 0);
	if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
		return (0);
	verif = get_grid(m, pos->x, pos->y + 1, 0);
	if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
		return (0);
	verif = get_grid(m, pos->x - 1, pos->y, 0);
	if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
		return (0);
	verif = get_grid(m, pos->x + 1, pos->y, 0);
	if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
		return (0);
	return (1);
}

int	check_map(t_map *m)
{
	t_point	pos;

	pos.x = 0;
	while (pos.x < m->width)
	{
		pos.y = 0;
		while (pos.y < m->height)
		{
			if (check_surround(m, &pos) == 0)
				return (0);
			pos.y++;
		}
		pos.x++;
	}
	return (1);
}
