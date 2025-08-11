/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:34:09 by brian             #+#    #+#             */
/*   Updated: 2025/08/11 22:36:02 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/canvas.h"
#include <math.h>

t_point	new_point(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_fpoint	new_fpoint(float x, float y)
{
	t_fpoint	new;

	new.x = x;
	new.y = y;
	return (new);
}

// float	calc_dist(t_fpoint p1, t_fpoint p2)
// {
// 	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)));
// }
