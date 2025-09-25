/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:30:48 by brian             #+#    #+#             */
/*   Updated: 2025/09/25 17:37:04 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cube3d.h"
# include "canvas.h"

typedef struct s_player
{
	t_fpoint	*position;
	float		angle;
}				t_player;

float		get_player_angle(char dir);

#endif
