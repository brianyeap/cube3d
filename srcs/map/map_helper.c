/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:54:30 by brian             #+#    #+#             */
/*   Updated: 2025/10/02 16:18:14 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	*ch_m(void *ptr, void *brain, char *msg)
{
	if (!ptr)
		exit_cube(brain, msg, 0);
	return (ptr);
}

int	set_player(t_player_detect **out, int x, char *line, int i)
{
	t_player_detect	*p;

	p = (t_player_detect *)malloc(sizeof(t_player_detect));
	if (p == NULL)
		exit_cube(NULL, "Error: malloc failed for player", 0);
	p->pos_x = x;
	p->direction = line[i];
	line[i] = '0';
	*out = p;
	return (1);
}
