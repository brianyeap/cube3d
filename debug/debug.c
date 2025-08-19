/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:47:16 by brian             #+#    #+#             */
/*   Updated: 2025/08/19 18:48:00 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	disp_point(t_fpoint p)
{
	dprintf(1, "{ x:%6f, y:%6f }\n", p.x, p.y);
}
