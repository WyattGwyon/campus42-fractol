/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:52:27 by clouden           #+#    #+#             */
/*   Updated: 2025/09/16 21:52:29 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color(int keysym, t_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (ctx->color[i].key != 0)
	{
		if (keysym == ctx->color[i].key)
		{
			ctx->fr.color_min = ctx->color[i].color_min;
			ctx->fr.color_max = ctx->color[i].color_max;
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
	while (ctx->event[i].event != NULL)
	{
		if (keysym == ctx->event[i].key)
		{
			ctx->event[i].event(ctx);
			fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
			break ;
		}
		i++;
	}
	return (0);
}

int	color_wrapper(int keysym, t_ctx *ctx)
{
	return (color(keysym, ctx));
}

int	shift_iterate_wrapper(int keysym, t_ctx *ctx)
{
	return (shift_iterate(keysym, ctx));
}

int	wrapper_handler(int keysym, t_ctx *ctx)
{
	size_t	i;

	i = 0;
	if (keysym == XK_Escape)
	{
		ft_printf("The %d key (ESC) has been pressed\n\n", keysym);
		cleanup((void *)&ctx->vars);
	}
	while (ctx->wrapper[i].wrapper != NULL)
	{
		if (keysym == ctx->wrapper[i].key)
		{
			ctx->wrapper[i].wrapper(keysym, ctx);
			break ;
		}
		i++;
	}
	return (0);
}

// int     change_color(t_vars *vars)
// {
//     // Fill the window with the current color
// //  mlx_clear_window(data->mlx, data->win);
//     mlx_string_put(vars->mlx_ptr, vars->win_ptr, 150, 150, vars->color, 
// 						"Color Changing Window!");
//     // Cycle through some basic colors: RED, GREEN, BLUE
//     if (vars->color == 0xFF0000)        // If it's red
//         vars->color = 0x00FF00;        // Change to green
//     else if (vars->color == 0x00FF00)   // If it's green
//         vars->color = 0x0000FF;        // Change to blue
//     else
//         vars->color = 0xFF0000;        // Otherwise, go back to red

//     return (0);
// }
