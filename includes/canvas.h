/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:01:30 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 17:46:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "MiniLib/mlx.h"

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_fpoint
{
	float		x;
	float		y;
}				t_fpoint;

typedef struct s_buff
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			offset;
	int			max_addr;
	double		ratio;
	int			initialized;
}				t_buff;

typedef struct s_ctx
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_ctx;

// Points
t_fpoint	new_fpoint(float x, float y);
float		calc_dist(t_fpoint p1, t_fpoint p2);

// Render
t_ctx		*new_ctx(int width, int height);

#endif