/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:18:44 by clouden           #+#    #+#             */
/*   Updated: 2025/09/11 18:18:51 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"



void	init_pix_coord(t_fract *fr, t_map *map)
{
	map->x_pix = 0;
	map->y_pix = 0;
	fr->x_coord = 0;
	fr->y_coord = 0;
	map->pix_per_unit = 10 ;
	map->pix_val = map->pix_per_unit / 100;
	map->x_foc = WIDTH / 2;
	map->y_foc = HEIGHT / 2;
};
void	set_xy_axis(t_fract *fr, t_vars *vars)
{
	for (int i = 0; i < WIDTH; ++i)
		put_pixel(&vars->img, i, ((HEIGHT / 2)), fr->color);
	for (int j = 0; j < HEIGHT; ++j)
		put_pixel(&vars->img, ((WIDTH / 2)), j, fr->color);
}

void	pixel_to_coord(t_map *map, t_fract *fr)
{
	fr->x_coord = (map->x_pix - map->x_foc) / map->pix_per_unit;
	fr->y_coord = (map->y_pix - map->y_foc) / (-1 * map->pix_per_unit);
}

void	coord_to_pixel(t_map *map, t_fract *fr)
{
	map->x_pix = (fr->x_coord * map->pix_per_unit) + map->x_foc;
	map->y_pix = (fr->y_coord * map->pix_per_unit) + map->y_foc;
}

// adjusts pix_per, around static focus point, based on pixel inputs
void	zoom(t_map *map)
{
	printf("zoom in on pixel (%f,%f)\n", map->x_pix, map->y_pix);
	
}
void	horizontal_shift(t_map *map) // move left/right a set number of pixels
{
	printf("horitonal_shift %f\n", map->x_pix);
}
void	vertical_shift(t_map *map) // move up/down a set number of pixels
{
	printf("vertical shift %f\n", map->y_pix);
}

// void	handle_event(t_op_type type, t_map *map, t_fract *fr)
// {
// 	if (type < OP_COUNT)
// 		operations[type](map, fr);
// }

void	plot_image(t_fract *fr, t_map *map, t_vars *vars)
{

	set_xy_axis(fr, vars);
	init_pix_coord(fr, map);
	while (map->y_pix < HEIGHT)
	{
		while (map->x_pix < WIDTH)
		{
			// mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, map->x_pix, map->y_pix, 0xffffff);
			pixel_to_coord(map, fr);
			if (mandel(fr->x_coord) == fr->y_coord)
			{
				put_pixel(&vars->img, map->x_pix, map->y_pix, fr->color);
				printf("[PLOTTED] ");
				printf("x_coord: %f   y-coord: %f   ", fr->x_coord, fr->y_coord);
				printf("x_pix: %f   y-pix: %f \n", map->x_pix, map->y_pix);
			}
			++map->x_pix;
		}
		map->x_pix = 0;
		++map->y_pix;
	}

	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img_ptr, 0, 0);
};
