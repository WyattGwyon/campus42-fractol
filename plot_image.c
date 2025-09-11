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
	map->pix_per_unit = 20;
	map->pix_val = map->pix_per_unit / 100;
	map->x_foc = WIDTH / 2;
	map->y_foc = HEIGHT / 2;
};
void	set_xy_axis(t_vars *vars)
{
	for (int i = 0; i < WIDTH; ++i)
		mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, i, ((HEIGHT / 2)), 0xffffff);
	for (int j = 0; j < HEIGHT; ++j)
		mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, (WIDTH / 2), j , 0xffffff);
	for (int k = 0; k < HEIGHT; k = k + (HEIGHT / 4))
		mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, (WIDTH / 2), k , 0x000000);
	for (int l = 0; l < WIDTH; l = l + (WIDTH / 4))
		mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, l , (HEIGHT / 2), 0x000000);
}

void	plot_image(t_fract *fr, t_map *map, t_vars *vars)
{
	set_xy_axis(vars);
	init_pix_coord(fr, map);
	while (map->x_pix < WIDTH)
	{
		printf("outloop");
		while (map->y_pix < HEIGHT)
		{
			// printf("innerloop");
			// mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, map->x_pix, map->y_pix, 0xffffff);
			// fr->x_coord = (map->x_pix - map->x_foc) / map->pix_per_unit;
			// fr->y_coord = (map->y_pix - map->y_foc) / map->pix_per_unit;
			// if (mandel(fr->x_coord) == fr->y_coord)
			// 	mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, map->x_pix, map->y_pix, fr->color);
			// ++map->y_pix;
		}
		++map->x_pix;
	}
	++map->x_pix;
};
