/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:15 by clouden           #+#    #+#             */
/*   Updated: 2025/09/15 16:31:17 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_pix_coord(t_graph *fr, t_pixel *map)
{
	map->x_pix = 0;
	map->y_pix = 0;
	map->pix_per_unit = 200;
	map->pix_val = map->pix_per_unit / 100;
	map->x_foc = (WIDTH / 3) * 2;
	map->y_foc = HEIGHT / 2;
	fr->x_coord = 0;
	fr->y_coord = 0;
	fr->escape_value = 5;
	fr->iterations = 42;
	fr->color_max = 0x000000;
	fr->color_min = 0xffffff;
	fr->shift_x = 0;
	fr->shift_y = 0;
	fr->max_x = 1.5;
	fr->min_x = -2.5;
	fr->max_y = 1.5;
	fr->min_y = -1.5;
	fr->zoom = 1.0;
}

void	init_vars(t_vars *vars)
{
	vars->mlx_ptr = NULL;
	vars->win_ptr = NULL;
	vars->img.img_ptr = NULL;
}

int	image_init(t_vars *vars, char **argv, t_graph *fr, t_pixel *map)
{
	init_vars(vars);
	fr->name = argv[1];
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		malloc_error();
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, fr->name);
	if (!vars->win_ptr)
	{
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		malloc_error();
	}
	vars->img.img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	if (!vars->img.img_ptr)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		malloc_error();
	}
	vars->img.pixel_data_addr = mlx_get_data_addr(vars->img.img_ptr, \
		&vars->img.bits_per_pixel, &vars->img.line_len, &vars->img.endian);
	init_pix_coord(fr, map);
	return (0);
}

void	init_tables(t_ctx *ctx)
{
	ctx->color = make_color_table();
	ctx->event = make_event_table();
	ctx->wrapper = make_wrapper_table();
}

// ft_printf("x_julia = %f y_julia = %f\n", ctx->fr.julia_x, ctx->fr.julia_y);
void	init_julia(t_ctx *ctx, char *argv[])
{
	ctx->fr.julia_x = ft_atof(argv[2]);
	ctx->fr.julia_y = ft_atof(argv[3]);
	ctx->fr.max_x = 2;
	ctx->fr.min_x = -2;
	ctx->fr.max_y = 2;
	ctx->fr.min_y = -2;
}
