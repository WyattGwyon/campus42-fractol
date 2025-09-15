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
	map->pix_per_unit = 10 ;
	map->pix_val = map->pix_per_unit / 100;
	map->x_foc = (WIDTH / 3) * 2;
	map->y_foc = HEIGHT / 2;
	fr->x_coord = 0;
	fr->y_coord = 0;
	fr->escape_value = 4;
	fr->iterations = 42;
}

void	init_ctx(t_ctx *ctx)
{
	t_vars		vars;
	t_pixel		map;
	t_graph		fr;

	init_pix_coord(ctx->fr, ctx->map);
	ctx->vars = &vars;
	ctx->map = &map;
	ctx->fr = &fr;
}

int	image_init(t_vars *vars, char **argv, t_graph *fr, t_pixel *map)
{
	vars->name = argv[1];
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		malloc_error();
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, vars->name);
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
	// TODO events_init(vars)
	//event_init();
	init_pix_coord(fr, map);
	return (0);
}
