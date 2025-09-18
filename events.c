/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:52:27 by clouden           #+#    #+#             */
/*   Updated: 2025/09/16 21:52:29 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_left(t_ctx *ctx) 
{
	ctx->fr.shift_x += (ctx->fr.max_x - ctx->fr.min_x) * -0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
}

void	move_right(t_ctx *ctx) 
{
	ctx->fr.shift_x += (ctx->fr.max_x - ctx->fr.min_x) * 0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
}

void	move_up(t_ctx *ctx)
{
	ctx->fr.shift_y += (ctx->fr.max_y - ctx->fr.min_y) * 0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
}

void	move_down(t_ctx *ctx)
{
	ctx->fr.shift_y += (ctx->fr.max_y - ctx->fr.min_y) * -0.1;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
}

void	iter_up(t_ctx *ctx)
{
	ctx->fr.iterations += 5;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	ft_printf("Iterations Set To: %d\n",ctx->fr.iterations);
}

void	iter_down(t_ctx *ctx)
{
	ctx->fr.iterations -= 5;
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	ft_printf("Iterations Set To: %d\n",ctx->fr.iterations);
}

void	reset(t_ctx *ctx)
{
	init_pix_coord(&ctx->fr, &ctx->map);
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
}

int	color(int keysym, t_ctx *ctx)
{
	size_t	i;

	i = 0;
	printf("The %d key has been pressed\n\n", keysym);
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		cleanup((void *)&ctx->vars);
	}
	while (i < sizeof(color_table)/sizeof(color_table[0]))
	{
		if (keysym == color_table[i].key)
		{
			ctx->fr.color_min = color_table[i].color_min;
			ctx->fr.color_max = color_table[i].color_max;
			fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
			break ;
		}
		i++;
	}
	return (0);
}

int	shift_iterate(int keysym, t_ctx *ctx)
{	
	size_t	i;

	i = 0;
	while (i < sizeof(event_table)/sizeof(event_table[0]))
	{
		if (keysym == event_table[i].key)
		{
			event_table[i].event(ctx);
			fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
			break ;
		}
		i++;
	}
	return (0);
}

int color_wrapper(int keysym, t_ctx *ctx)
{
	return (color(keysym, ctx));
}

int shift_iterate_wrapper(int keysym, t_ctx *ctx)
{
	return (shift_iterate(keysym, ctx));
}

int	key_handler(int keysym, t_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (key_table[i].event != NULL)
	{
		if (keysym == key_table[i].key)
		{
			key_table[i].event(keysym, ctx);
			break ;
		}
		i++;
	}
	return (0);
}