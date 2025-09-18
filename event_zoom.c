/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_zoom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:24:36 by clouden           #+#    #+#             */
/*   Updated: 2025/09/18 20:24:38 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	iter_up(t_ctx *ctx)
{
	ctx->fr.iterations += 5;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	ft_printf("Iterations Set To: %d\n",ctx->fr.iterations);
	return (0);
}

int	iter_down(t_ctx *ctx)
{
	ctx->fr.iterations -= 5;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	ft_printf("Iterations Set To: %d\n",ctx->fr.iterations);
	return (0);
}

void	zoom_in(t_ctx *ctx, double zoom, int x_pix, int y_pix)
{
	double	x_zoom;
	double	y_zoom;
	double	x_len;
	double	y_len;
	double	to_x_min_pix;
	double	to_x_max_pix;
	double	to_y_min_pix;
	double	to_y_max_pix;

	x_len = ctx->fr.max_x - ctx->fr.min_x;
	y_len = ctx->fr.max_y - ctx->fr.min_y;
	x_zoom = x_len * zoom;
	y_zoom = y_len * zoom;
	to_x_min_pix = (double)x_pix / (double)WIDTH;
	to_x_max_pix = ((double)WIDTH - (double)x_pix) / (double)WIDTH;
	to_y_min_pix = (double)y_pix / (double)HEIGHT;
	to_y_max_pix = ((double)HEIGHT - (double)y_pix) / (double)HEIGHT;
	ctx->fr.min_x += x_zoom * (double)to_x_min_pix;
	ctx->fr.max_x -= x_zoom * (double)to_x_max_pix;
	ctx->fr.min_y += y_zoom * (double)to_y_min_pix;
	ctx->fr.max_y -= y_zoom * (double)to_y_max_pix;
}

void	zoom_out(t_ctx *ctx, double zoom, int x_pix, int y_pix)
{
	double	x_zoom;
	double	y_zoom;
	double	x_len;
	double	y_len;
	double	to_x_min_pix;
	double	to_x_max_pix;
	double	to_y_min_pix;
	double	to_y_max_pix;

	x_len = ctx->fr.max_x - ctx->fr.min_x;
	y_len = ctx->fr.max_y - ctx->fr.min_y;
	x_zoom = x_len * zoom;
	y_zoom = y_len * zoom;
	to_x_min_pix = (double)x_pix / (double)WIDTH;
	to_x_max_pix = ((double)WIDTH - (double)x_pix) / (double)WIDTH;
	to_y_min_pix = (double)y_pix / (double)HEIGHT;
	to_y_max_pix = ((double)HEIGHT - (double)y_pix) / (double)HEIGHT;
	ctx->fr.min_x -= x_zoom * (double)to_x_min_pix;
	ctx->fr.max_x += x_zoom * (double)to_x_max_pix;
	ctx->fr.min_y -= y_zoom * (double)to_y_min_pix;
	ctx->fr.max_y += y_zoom * (double)to_y_max_pix;
}

int	button_press(int button, int x, int y, t_ctx *ctx)
{
	if (button == 1)
	{
		printf("Left mouse button pressed at (%d, %d)!\n", x, y);
	}
	else if (button == 3)
	{
		printf("Right mouse button pressed at (%d, %d)!\n", x, y);
	}
	else if (button == 4)
	{
		ctx->fr.iterations += 4;
		zoom_in(ctx, 0.40, x, y);
		printf("x_max = %f x_min = %f\n", ctx->fr.max_x, ctx->fr.min_x);
		printf("Zoom in scroll at (%d, %d)!\n", x, y);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (button == 5)
    {
		ctx->fr.iterations -= 2;
		zoom_out(ctx, 0.20, x, y);
		printf("Zoom out scroll at (%d, %d)!\n", x, y);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	return (0);
}
