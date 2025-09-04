/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:40:21 by brian             #+#    #+#             */
/*   Updated: 2025/09/02 20:34:23 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	action_keys(int key, void *param, t_brain *b)
{
	(void)key;
	(void)param;
	(void)b;
	/* intentionally empty */
}

int key_press(int key, void *param)
{
    t_brain *b = (t_brain *)param;

    if (key == -1) {
        // held-keys tick
        for (int i = 0; i < 10 && b->keys[i] != -1; i++)
            rc_boot_keydown(b->keys[i], b);   // <-- call directly
        return 0;
    }

    add_key_pressed(b, key);
    rc_boot_keydown(key, b);                  // <-- call directly

    // action_keys(key, param, b);            // if you need your own actions too
    return 0;
}


int key_release(int key, void *param)
{
    t_brain *b = (t_brain *)param;

    del_key_pressed(b, key);
    return (0);
}