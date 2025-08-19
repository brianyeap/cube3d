/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:01:30 by brian             #+#    #+#             */
/*   Updated: 2025/08/18 02:01:30 by brian            ###   ########.fr       */
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
	int			color;
	int			line_width;
	void		*mlx_ptr;
	void		*win_ptr;
	t_buff		*buff;
	t_buff		*cur_buff;
	t_fpoint	divided;
	float		col_step;
	void		(*line)(t_point, t_point, struct s_ctx *);
	void		(*rect)(t_point, t_point, int, struct s_ctx *);
	void		(*circle)(t_fpoint, int, int, struct s_ctx *);
	void		(*clear)(int, struct s_ctx *);
}				t_ctx;

// Points
t_point		new_point(int x, int y);
t_fpoint	new_fpoint(float x, float y);

// Render
t_ctx		*new_ctx(int width, int height);

#endif