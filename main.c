/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:30:25 by clouden           #+#    #+#             */
/*   Updated: 2025/09/01 20:30:28 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_ctx		ctx;

	if (argc < 2)
		return (ft_printf(
		"fractol: usage: Please enter:\n\t\"%s mandelbrot\" or\n"
		"\t\"%s julia <float_1> <float_2>\"\n", argv[0], argv[0]), 0);
	ctx.fr.name = argv[1];
	if (argc == 2 && !ft_strncmp(ctx.fr.name, "mandelbrot", 10))
	{
		// TODO
		if (image_init(&ctx.vars, argv, &ctx.fr, &ctx.map))
			return (1);
		init_pix_coord(&ctx.fr, &ctx.map);
		fractal_render(&ctx.fr, &ctx.map, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, &wrapper_handler, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, ButtonPress, ButtonPressMask, &button_press, &ctx);
		mlx_hook(ctx.vars.win_ptr, DestroyNotify, 0, &cleanup, &ctx.vars);
		mlx_loop(ctx.vars.mlx_ptr);
		ft_printf("%s\n", ctx.fr.name);
		return (0);
	}
	else if (argc == 2 && !ft_strncmp(ctx.fr.name, "newton", 6))
	{
		if (image_init(&ctx.vars, argv, &ctx.fr, &ctx.map))
			return (1);
		init_pix_coord(&ctx.fr, &ctx.map);
		newton_render(&ctx.fr, &ctx.map, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, &wrapper_handler, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, ButtonPress, ButtonPressMask, &button_press, &ctx);
		mlx_hook(ctx.vars.win_ptr, DestroyNotify, 0, &cleanup, &ctx.vars);
		mlx_loop(ctx.vars.mlx_ptr);
		ft_printf("%s\n", ctx.fr.name);
	}
	else if (argc == 4 && !ft_strncmp(ctx.fr.name, "julia", 5))
	{
		// TODO
		if (image_init(&ctx.vars, argv, &ctx.fr, &ctx.map))
		return (1);
		init_pix_coord(&ctx.fr, &ctx.map);
		ctx.fr.julia_x = ft_atof(argv[2]);
		ctx.fr.julia_y = ft_atof(argv[3]);
		ctx.fr.max_x = 2;
		ctx.fr.min_x = -2;
		ctx.fr.max_y = 2;
		ctx.fr.min_y = -2;
		fractal_render(&ctx.fr, &ctx.map, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, &wrapper_handler, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, ButtonPress, ButtonPressMask, &button_press, &ctx);
		mlx_hook(ctx.vars.win_ptr, DestroyNotify, 0, &cleanup, &ctx.vars);
		mlx_loop(ctx.vars.mlx_ptr);
		ft_printf("%s\n", ctx.fr.name);
		ft_printf("%f %f\n", ctx.fr.julia_x, ctx.fr.julia_y);
	}
}
