/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:52:05 by brian             #+#    #+#             */
/*   Updated: 2025/09/02 20:30:07 by brian            ###   ########.fr       */
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

int	is_key_pressed(t_brain *b, int key)
{
	int	i;

	i = 0;
	while (i < 10 && key != -1)
	{
		if (b->keys[i] == key)
			return (i);
		i++;
	}
	return (-1);
}

int	add_key_pressed(t_brain *b, int key)
{
	int	i;

	i = 0;
	while (b->keys[i] != -1 && i < 10)
		i++;
	if (i < 10)
	{
		b->keys[i] = key;
		return (1);
	}
	return (0);
}

int	del_key_pressed(t_brain *b, int key)
{
	int	i;

	i = 0;
	while (b->keys[i] != key && i < 10)
		i++;
	if (i < 10 && b->keys[i] == key)
	{
		b->keys[i] = -1;
		return (1);
	}
	return (0);
}

static void forward_to_boot_if_needed(int key, t_brain *b)
{
    // Forward to the boot renderer controls (W/S/A/D/ESC)
    // Safe to call for any key; it ignores non-relevant ones.
    rc_boot_keydown(key, b);
}


