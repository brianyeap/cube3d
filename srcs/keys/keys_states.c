/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:52:05 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 18:42:24 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	init_keys(t_brain *b)
{
	int	i;

	i = 0;
	b->keys = ft_calloc(10, sizeof(int));
	while (i < 10)
		b->keys[i++] = -1;
}

int	add_key_pressed(t_brain *b, int key)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		if (b->keys[i] == key)
			return (1);
		i++;
	}

	i = 0;
	while (i < MAX_KEYS)
	{
		if (b->keys[i] == -1)
		{
			b->keys[i] = key;
			return (1);
		}
		i++;
	}
	return (0);
}

int	del_key_pressed(t_brain *b, int key)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		if (b->keys[i] == key)
		{
			b->keys[i] = -1;
			return (1);
		}
		i++;
	}
	return (0);
}



