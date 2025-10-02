/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_boot.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:21:51 by brian             #+#    #+#             */
/*   Updated: 2025/10/02 17:08:37 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RC_BOOT_H
# define RC_BOOT_H

# define RC_TURN 0.03f
# define RC_SPEED 2.0f

typedef struct s_ray
{
	double		map_area;
	double		fov;
	double		pos_x; /* player position in tiles */
	double		pos_y;
	double		dir_x; /* normalized direction */
	double		dir_y;
	double		plane_len; /* half-width of camera plane */
	double		plane_x; /* camera plane vector */
	double		plane_y;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			side; /* 0 NS, 1 EW */
	int			hit;
	int			out_of_bounds;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start0; // unclamped values
	int			draw_end0;
	int			draw_start; // clamped values
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	double		scale_x;
	double		scale_y;
	int			px_x_start;
}	t_ray;

typedef struct s_brain	t_brain;

// rc boot draw4
void	render_sky(t_brain *b, int x);
void	render_wall_texture(t_brain *b, int x);
void	render_floor(t_brain *b, int x);

// rc boot draw3
void	calc_perp_wall(t_brain *b);
void	calculate_line_height(t_brain *b);
void	calculate_draw_bounds(t_brain *b);
void	calculate_wall_rendering(t_brain *b);
void	calculate_texture_x(t_brain *b);

// rc boot draw2
void	perform_dda(t_brain *b);
void	calculate_step(t_brain *b);
void	ray_setup(t_brain *b, int x);
void	init_dda(t_brain *b);

// rc boot draw
void	clear_img(t_brain *b);
void	draw_3d(t_brain *b);
void	perform_raycast(t_brain *b, int x);
int		get_texture_pixel(t_brain *b, int tex_x, int tex_y);

// rc draw minimap
void	rc_draw_minimap(t_brain *b);

// rc boot hook
int		rc_boot_loop(t_brain *b);
int		rc_boot_keydown(int key, t_brain *b);

// rc boot init
int		rc_boot_init(t_brain *b);
void	rc_boot_attach_world(t_brain *b);
void	put_px(t_brain *b, int x, int y, int color);

// rc boot world
int		cell_at(t_brain *b, int mx, int my);
int		is_blocking(int v);
int		hit(t_brain *b, float x, float y);

// rc boot movement
void	rc_update_dir(t_brain *b);
void	rc_wrap_angle(t_brain *b);

int		rc_boot_key_up(t_brain *b);
int		rc_boot_key_down(t_brain *b);
int		rc_boot_turn_left(t_brain *b);
int		rc_boot_turn_right(t_brain *b);
int		rc_boot_move_right(t_brain *b);
int		rc_boot_move_left(t_brain *b);

#endif /* RC_BOOT_H */