/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:27:42 by brian             #+#    #+#             */
/*   Updated: 2025/08/11 23:59:58 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/canvas.h"
#include "../../includes/cube3d.h"

t_ctx	*new_ctx(int width, int height)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = 0;
	ctx->width = width;
	ctx->height = height;
	ctx->divided = new_fpoint(width / 2, height / 2);
	ctx->col_step = 0;
	// ctx->line = &draw_line;
	// ctx->rect = &draw_rect;
	// ctx->circle = &draw_circle;
	// ctx->text = &put_text;
	// ctx->clear = &clear_ctx;
	return (ctx);
}

void	init_buff(t_ctx *ctx, t_buff **buff, int width, int height)
{
	(*buff) = malloc(sizeof(t_buff));
	if ((*buff) == NULL)
		exit_cube(NULL, "Failed to malloc buff", 0);
	(*buff)->width = width;
	(*buff)->height = height;
	ft_printf("INIT BUFF %d x %d px\n", width, height);
	(*buff)->img = NULL;
	(*buff)->addr = NULL;
	(*buff)->img = mlx_new_image(ctx->mlx_ptr, ctx->width, ctx->height);
	(*buff)->addr = mlx_get_data_addr((*buff)->img, &(*buff)->bits_per_pixel,
			&(*buff)->line_length,
			&(*buff)->endian);
	(*buff)->max_addr = (*buff)->line_length * (*buff)->height;
	(*buff)->offset = (*buff)->bits_per_pixel / 8;
	if ((*buff)->addr == NULL)
		exit_cube(NULL, "Buff address not set", 0);
	if ((*buff)->img == NULL)
		exit_cube(NULL, "Buff image not set", 0);
}
