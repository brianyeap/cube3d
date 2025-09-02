/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:40:21 by brian             #+#    #+#             */
/*   Updated: 2025/09/02 19:40:32 by brian            ###   ########.fr       */
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

int		key_press(int key, void *param)
{
	(void)key;
	(void)param;
	/* intentionally empty */
	return (0);
}

int		key_release(int key, void *param)
{
	(void)key;
	(void)param;
	/* intentionally empty */
	return (0);
}