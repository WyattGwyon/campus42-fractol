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

void	enter_the_fractol(t_ctx *ctx, char *argv[])
{
	if (!ft_strncmp(ctx->fr.name, "julia", 5))
	{
		init_pix_coord(&ctx->fr, &ctx->map);
		init_julia(ctx, argv);
		if (image_init(&ctx->vars, argv, &ctx->fr, &ctx->map))
			exit (EXIT_FAILURE);
	}
	else
	{
		if (image_init(&ctx->vars, argv, &ctx->fr, &ctx->map))
			exit (EXIT_FAILURE);
		init_pix_coord(&ctx->fr, &ctx->map);
	}
	init_tables(ctx);
	fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
}

int	main(int argc, char **argv)
{
	t_ctx		ctx;

	ft_bzero(&ctx, sizeof(ctx));
	if (argc < 2)
		return (usage_error(argv), 0);
	ctx.fr.name = argv[1];
	if ((argc == 2 && (!ft_strncmp(ctx.fr.name, "mandelbrot", 10) || \
			!ft_strncmp(ctx.fr.name, "tricorn", 7) || \
			!ft_strncmp(ctx.fr.name, "celtic", 6) || \
			!ft_strncmp(ctx.fr.name, "burningship", 11))) || \
			(argc == 4 && !ft_strncmp(ctx.fr.name, "julia", 5)))
	{
		enter_the_fractol(&ctx, argv);
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, &wrapper_handler,
			&ctx.vars);
		mlx_hook(ctx.vars.win_ptr, ButtonPress, ButtonPressMask, &mouse_events,
			&ctx);
		mlx_hook(ctx.vars.win_ptr, DestroyNotify, 0, &cleanup, &ctx.vars);
		mlx_loop(ctx.vars.mlx_ptr);
	}
	else
		return (usage_error(argv), 0);
}
