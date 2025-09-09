/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:30:36 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 18:16:48 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube3d.h"

typedef struct s_sprite
{
	t_fpoint	pos;
	int			type;
	float		deg;
	int			on_screen;
	t_buff		*model;
	t_buff		*shadow;
	float		dist;
}				t_sprite;

typedef struct s_map_line
{
	int	length;
	int	*line;
}				t_map_line;

typedef struct s_spr_list
{
	int			*column;
	int			length;
	t_sprite	**list;
}				t_spr_list;

typedef struct s_map
{
	t_map_line	**grid;
	int			width;
	int			height;
	int			px_width;
	int			px_height;
	int			bloc_size;
	float		scale;
	t_fpoint	disp;
	int			sprites_count;
	t_spr_list	*sprites;
	t_buff		*w_n;
	t_buff		*w_e;
	t_buff		*w_s;
	t_buff		*w_w;
	t_buff		*floor;
	t_buff		*frame;
	t_buff		*skybox;
	void		*brain;
}				t_map;

typedef struct s_player_detect
{
	int			pos_x;
	char		direction;
}				t_player_detect;


t_player_detect		*add_map_row(t_map *m, char *line);
t_player_detect		*chr_trt(char *line, t_map *m);
int					realloc_map(t_map *m, char *line);
int					init_map(void *brain);

#endif