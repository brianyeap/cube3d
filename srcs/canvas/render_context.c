/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:27:42 by brian             #+#    #+#             */
/*   Updated: 2025/09/28 00:33:04 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/canvas.h"
#include "../../includes/cube3d.h"

t_ctx	*new_ctx()
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = 0;
	return (ctx);
}
