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

// int     change_color(t_vars *vars)
// {
//     // Fill the window with the current color
// //  mlx_clear_window(data->mlx, data->win);
//     mlx_string_put(vars->mlx_ptr, vars->win_ptr, 150, 150, vars->color, "Color Changing Window!");

//     // Cycle through some basic colors: RED, GREEN, BLUE
//     if (vars->color == 0xFF0000)        // If it's red
//         vars->color = 0x00FF00;        // Change to green
//     else if (vars->color == 0x00FF00)   // If it's green
//         vars->color = 0x0000FF;        // Change to blue
//     else
//         vars->color = 0xFF0000;        // Otherwise, go back to red

//     return (0);
// }

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

int     button_press(int button, int x, int y, t_ctx *ctx)
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

int	handle_input(int keysym, t_vars *vars)
{
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
        mlx_destroy_display(vars->mlx_ptr);
        free(vars->mlx_ptr);
        exit(1);
    }
    printf("The %d key has been pressed\n\n", keysym);
    return (0);
}

void	color_screen(t_vars *vars, int color)
{
	int y = 0;
	while (y < HEIGHT)	
	{
		int x = 0;
		while (x < WIDTH)
		{
			put_pixel(&vars->img, x, y, color);
			++x;
		}
		++y;
	}
}

int	main(int argc, char **argv)
{
	// t_parser	*data;
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
		// mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, &color, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, &key_handler, &ctx.vars);
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
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, color, &ctx.vars);
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
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, color, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, ButtonPress, ButtonPressMask, &button_press, &ctx);
		mlx_hook(ctx.vars.win_ptr, DestroyNotify, 0, &cleanup, &ctx.vars);
		mlx_loop(ctx.vars.mlx_ptr);
		ft_printf("%s\n", ctx.fr.name);
		ft_printf("%f %f\n", ctx.fr.julia_x, ctx.fr.julia_y);
	}
	// else
	// {
	// 	clean_parser(&data);
	// 	return (ft_printf(
	// 		"fractol: usage: Please enter:\n\t\"%s mandelbrot\" or\n"
	// 		"\t\"%s julia <float_1> <float_2>\"\n", argv[0], argv[0]), 0);
	// }
	// clean_parser(&data);
}
