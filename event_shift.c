/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:06:46 by clouden           #+#    #+#             */
/*   Updated: 2025/09/18 15:06:49 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	reset(t_ctx *ctx)
{
	init_pix_coord(&ctx->fr, &ctx->map);
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	return (0);
}

int	move_left(t_ctx *ctx)
{
	ctx->fr.shift_x += (ctx->fr.max_x - ctx->fr.min_x) * -0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	return (0);
}

int	move_right(t_ctx *ctx)
{
	ctx->fr.shift_x += (ctx->fr.max_x - ctx->fr.min_x) * 0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	return (0);
}

int	move_up(t_ctx *ctx)
{
	ctx->fr.shift_y += (ctx->fr.max_y - ctx->fr.min_y) * -0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	return (0);
}

int	move_down(t_ctx *ctx)
{
	ctx->fr.shift_y += (ctx->fr.max_y - ctx->fr.min_y) * 0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	return (0);
}
