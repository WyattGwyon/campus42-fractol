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
	const t_color_map	*color_table = gctable();
	size_t				i;

	i = 0;
	while (color_table[i].key != 0)
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
	const t_event_map	*event_table = getable();
	size_t				i;

	i = 0;
	while (event_table[i].event != NULL)
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
	const t_wrapper_map	*wrapper_table = gwtable();
	size_t				i;

	i = 0;
	if (keysym == XK_Escape)
	{
		ft_printf("The %d key (ESC) has been pressed\n\n", keysym);
		cleanup((void *)&ctx->vars);
	}
	while (wrapper_table[i].wrapper != NULL)
	{
		if (keysym == wrapper_table[i].key)
		{
			wrapper_table[i].wrapper(keysym, ctx);
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
