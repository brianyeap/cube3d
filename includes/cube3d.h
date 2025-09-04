/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:22:12 by brian             #+#    #+#             */
/*   Updated: 2025/09/04 20:58:33 by brian            ###   ########.fr       */
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
# include "../debug/debug.h"

# define RST	"\033[0m"
# define RED    "\033[0;31m"
# define GRN    "\033[0;32m"
# define YELO   "\033[0;33m"
# define BLUE   "\033[0;34m"
# define PINK   "\033[0;35m"
# define CYAN   "\033[0;36m"
# define GREY   "\033[0;90m"
# define PURP   "\033[0;94m"

typedef struct s_rcboot {
  void  *img;
  char  *data;
  int    bpp;
  int    stride;
  int    endian;

  float  px, py;   // player position (boot view)
  float  pa;       // angle
  float  pdx, pdy; // derived from angle
  int    tile;     // tile size

  t_map *world;    // points to b->map
  int    w, h;     // render size (RC_W, RC_H)
} t_rcboot;

typedef struct s_brain
{
	int			initialized;
	t_ctx		*ctx;
	t_map		*map;
	t_player	*player;
	int			*keys;
  	t_rcboot *rc;    // <-- add this
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
void		exit_cube(t_brain *brain, char *msg, int exit_now);

// Checker
void		ft_init_t_type(t_type *map);
void		ft_getmap_values(char *line, t_type *map);
void		ft_set_resolution(char *str, int *target, t_type *map);
char		*ft_check_str(char *str, char *chrs);
void		parse_texture_path(char *str, char **target, t_type *map);
t_type		*ft_getmap_config(char *file);

// Map
int			get_grid(t_map *m, int x, int y, int need_rescale);
t_fpoint	to_grid(int x, int y, t_map *m);
int			init_map(t_ctx *ctx, void *brain);
void		init_textures(t_brain *b, t_type *map);
int			open_map(t_brain *b, char *map_path, t_type *map);

// Player
int			init_player(t_brain *b, int pos_x, char angle);

// Map Helper
void		*ch_m(void *ptr, void *brain, char *msg);

// Textures
void		init_texture(t_brain *b, char *path, t_buff **t);

// Checker Utils
int			check_map(t_map *m);
void		ft_exit(char *str, t_type *map);
void		ft_check_struct(t_type *map);
int			check_surround(t_map *m, t_point *pos);

// Canvas
void		init_buff(t_ctx *ctx, t_buff **buff, int width, int height);

// Keys
void		init_keys(t_brain *b);

// Utilities
int			ft_strmultichr(char *str, char *chrlst);
int			check_ending(char *str, char *end);
void		sort_sprites(t_fpoint *pos, t_spr_list *lst_sprt);

// Sprites
void		add_spr_to_list(t_spr_list *s_list, t_sprite *s);
t_sprite	*init_sprite(t_map *m, t_fpoint pos, int type);

void		action_keys(int key, void *param, t_brain *b);
int			key_press(int key, void *param);
int			key_release(int key, void *param);

// Boot raycaster (temporary smoke test renderer)
int rc_boot_init(t_brain *b);
int rc_boot_loop(t_brain *b);
int rc_boot_keydown(int key, t_brain *b);

void forward_to_boot_if_needed(int key, t_brain *b);
int	add_key_pressed(t_brain *b, int key);
int	del_key_pressed(t_brain *b, int key);
int key_press(int key, void *param);

void rc_boot_attach_world(t_brain *b);

#endif