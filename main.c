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
		ctx->fr.min_x -= (((double)x / (double)WIDTH) * 0.1); 
		ctx->fr.max_x -= ((((double)WIDTH - (double)x) / (double)WIDTH) * 0.1);
		ctx->fr.min_y -= (((double)y / (double)HEIGHT) * 0.1); 
		ctx->fr.max_y -= ((((double)HEIGHT - (double)y) / (double)HEIGHT) * 0.1); 
		printf("x_max = %f x_min = %f\n", ctx->fr.max_x, ctx->fr.min_x);
		printf("Zoom in scroll at (%d, %d)!\n", x, y);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (button == 5)
    {
		ctx->fr.min_x += (((double)x / (double)WIDTH) * 0.1); 
		ctx->fr.max_x += ((((double)WIDTH - (double)x) / (double)WIDTH) * 0.1);
		ctx->fr.min_y += (((double)y / (double)HEIGHT) * 0.1); 
		ctx->fr.max_y += ((((double)HEIGHT - (double)y) / (double)HEIGHT) * 0.1); 
		printf("Zoom out scroll at (%d, %d)!\n", x, y);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}

    return (0);
}

int	handle_input(int keysym, t_vars *vars)
{
    //Check the #defines
    //find / -name keysym.h 2>/dev/null
    //find / -name keysymdef.h 2>/dev/null
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
			break;
		}
		i++;
	}
	
	if (keysym == XK_Up)
	{
		ctx->fr.shift_y += 0.1;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (keysym == XK_Down)
	{
		ctx->fr.shift_y += -0.1;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (keysym == XK_Left)
	{
		ctx->fr.shift_x += 0.1;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (keysym == XK_Right)
	{
		ctx->fr.shift_x += -0.1;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (keysym == XK_l)
	{
		ctx->fr.iterations -= 5;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
		ft_printf("Iterations Set To: %d\n",ctx->fr.iterations);
	}
	else if (keysym == XK_h)
	{
		ctx->fr.iterations += 5;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
		ft_printf("Iterations Set To: %d\n",ctx->fr.iterations);
	}
	else if (keysym == XK_r)
	{
		init_pix_coord(&ctx->fr,&ctx->map);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}

	return 0;
}

int motions(int keysym, t_ctx *ctx)
{
	size_t	i;

	i = 0;
	printf("The %d key has been pressed\n\n", keysym);
	if (keysym == Button4)
	{
		ctx->fr.color_min = 0x006600;
		ctx->fr.color_max = 0x339933;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (keysym == Button5)
	{
		ctx->fr.color_min = 0x301860;
		ctx->fr.color_max = 0x602080;
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
			
	mlx_put_image_to_window(ctx->vars.mlx_ptr, ctx->vars.win_ptr, 
							ctx->vars.img.img_ptr, 0, 0);
	return 0;
}



// int main(void)
// {
// 	t_vars vars;
// 	t_graph fr;
// 	t_pixel	map;

// 	fr.color = 0xffffff;
// 	if (image_init(&vars))
// 		return (1);
// 	printf("Line_len %d <-> WIDTH%d HEIGHT%d\n"
// 			"bpp %d\n"
// 			"endian %d\n", vars.img.line_len, WIDTH, HEIGHT, vars.img.bits_per_pixel, vars.img.endian);
// 	mlx_hook(vars.win_ptr, ButtonPress, ButtonPressMask, &button_press, &vars);
// 	mlx_hook(vars.win_ptr, DestroyNotify, 0, &cleanup, &vars);
// 	plot_image(&fr, &map, &vars);
// 	// set_xy_axis(&vars);
// 	// mlx_loop_hook(vars.mlx_ptr, change_color, &vars);
// 	// mlx_pixel_put(vars.mlx_ptr, vars.win, (WIDTH / 2), (HEIGHT / 2), 0xffffff);
// 	mlx_key_hook(vars.win_ptr, f, &vars);
// 	mlx_loop(vars.mlx_ptr);
// 	// mlx_do_sync(vars.mlx_ptr);
// 	// mlx_key_hook(vars.win, handle_input, &vars);
// 	// mlx_destroy_window(vars.mlx_ptr, vars.win);
// 	// mlx_destory_display(vars.mlx_ptr);
// 	// free(vars.mlx_ptr);
// }


// int main(void)
// {
// 	t_complex 	z;
// 	t_complex 	c;
// 	int 		i;
// 	double		tmp_real;
	
// 	z.real = 0;
// 	z.i = 0;

// 	c.real = 0.25;
// 	c.i = 0.4;

// 	i = 0;
// 	while (i < 42)
// 	{
// 		// z = z² + c
// 		// First resolve z² which is made up of
// 		// (Real + imaginary)
// 		tmp_real = (z.real * z.real) - (z.i * z.i);
// 		z.i = 2 * z.real * z.i;
// 		z.real = tmp_real;

// 		// Add z² to c
// 		z.real += c.real;
// 		z.i += c.i;

// 		printf("iteration n -> %d real %f imaginary %f\n", i, z.real, z.i);
// 		++i;
// 	}

// }

int	main(int argc, char **argv)
{
	t_parser	*data;
	t_ctx		ctx;

	if (argc < 2)
	return (ft_printf(
		"fractol: usage: Please enter:\n\t\"%s mandelbrot\" or\n"
		"\t\"%s julia <float_1> <float_2>\"\n", argv[0], argv[0]), 0);
		if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		{
			// TODO
		if (image_init(&ctx.vars, argv, &ctx.fr, &ctx.map))
			return (1);
		init_pix_coord(&ctx.fr, &ctx.map);
		fractal_render(&ctx.fr, &ctx.map, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, KeyPress, KeyPressMask, color, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, ButtonPress, ButtonPressMask, &button_press, &ctx);
		// mlx_mouse_hook(ctx.vars.win_ptr, motions, &ctx.vars);
		mlx_hook(ctx.vars.win_ptr, DestroyNotify, 0, &cleanup, &ctx.vars);
		mlx_loop(ctx.vars.mlx_ptr);
		ft_printf("mandelbrot\n");
		return (0);
	}
	data = parse_controller(argc, argv);
	if (!data)
		return (write(2, "Error\n", 6), 1);
	if (!data->intarr)
	{
		ft_strarr_free(&data->strarr);
		free(data);
		return (write(2, "Error\n", 6), 1);
	}
	else if (data->len == 2 && !ft_strncmp(argv[1], "julia", 5))
	{
		// TODO
		if (image_init(&ctx.vars, argv, &ctx.fr, &ctx.map))
 			return (1);
		ft_printf("julia\n");
		printf("%f %f\n", data->intarr[0], data->intarr[1]);
	}
	else
	{
		clean_parser(&data);
		return (ft_printf(
			"fractol: usage: Please enter:\n\t\"%s mandelbrot\" or\n"
			"\t\"%s julia <float_1> <float_2>\"\n", argv[0], argv[0]), 0);
	}
}
