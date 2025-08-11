/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:22:12 by brian             #+#    #+#             */
/*   Updated: 2025/08/12 01:38:09 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <string.h>
# include <math.h>
# include "MiniLib/mlx.h"
# include "../libft/libft.h"
# include "canvas.h"
# include "player.h"
# include "map.h"

typedef struct s_brain
{
	int			initialized;
	t_ctx		*ctx;
	t_map		*map;
	t_player	*player;
	int			*keys;
}				t_brain;

typedef struct s_type
{
	int			fd;
	int			height;
	int			width;
	int			valid;
	int			res[3];
	char		*line;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	char		*f;
	char		*c;
}				t_type;

// Cleanups
void	exit_cube(t_brain *brain, char *msg, int exit_now);

// Checker
void	ft_init_t_type(t_type *map);
void	ft_getmap_values(char *line, t_type *map);
void	ft_set_resolution(char *str, int *target, t_type *map);
char	*ft_check_str(char *str, char *chrs);
void	parse_texture_path(char *str, char **target, t_type *map);
t_type	*ft_getmap_config(char *file);

// Checker Utils
void	ft_exit(char *str, t_type *map);
void	ft_check_struct(t_type *map);

// Canvas
void	init_buff(t_ctx *ctx, t_buff **buff, int width, int height);

// Keys
void	init_keys(t_brain *b);

// Utilities
int		ft_strmultichr(char *str, char *chrlst);
int		check_ending(char *str, char *end);

#endif