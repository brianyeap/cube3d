/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:40:21 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 17:20:13 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	key_press(int key, void *param)
{
	t_brain	*b;
	int		i;

	b = (t_brain *)param;
	if (key == -1)
	{
		i = 0;
		while (i < 10 && b->keys[i] != -1)
		{
			rc_boot_keydown(b->keys[i], b);
			i++;
		}
		return (0);
	}
	add_key_pressed(b, key);
	rc_boot_keydown(key, b);
	return (0);
}

int	key_release(int key, void *param)
{
	t_brain	*b;

	b = (t_brain *)param;
	del_key_pressed(b, key);
	return (0);
}
