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

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return (((new_max - new_min) * (unscaled_num / old_max)) + new_min); 
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

	*((unsigned int *)(offset + img->pixel_data_addr)) = color;
}

void	mandel_or_julia(t_complex *z, t_complex *c, t_graph *fr)
{
	if (!ft_strncmp(fr->name, "julia", 5))
	{
		c->real = fr->julia_x;
		c->i = fr->julia_y;
	}
	else
	{
		c->real = z->real;
		c->i = z->i;
	}
}

void	handle_pixel(int x, int y, t_img *img, t_graph *fr)
{
	t_complex	z;
	t_complex	c;
	int			i;
	
	i = 0;
	z.real = map(x, fr->min_x, fr->max_x, WIDTH) + fr->shift_x;
	z.i = map(y, fr->min_y, fr->max_y, HEIGHT) + fr->shift_y; // TODO height should have the same scale
	mandel_or_julia(&z, &c, fr);
	while (i < fr->iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.i * z.i) > fr->escape_value)
		{
			fr->color = map(i, fr->color_max, fr->color_min, fr->iterations);
			put_pixel(img, x, y, fr->color);
			return ;
		}
		i++;
	}
	put_pixel(img, x, y, BLACK);
}

void	fractal_render(t_graph *fr, t_pixel *map, t_vars *vars)
{
	t_img	temp;

	temp.img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	temp.pixel_data_addr = mlx_get_data_addr(temp.img_ptr, &temp.bits_per_pixel,
				&temp.line_len, &temp.endian);
	map->y_pix = 0;
	while (map->y_pix < HEIGHT)
	{
		map->x_pix = 0;
		while (map->x_pix < WIDTH)
		{
			handle_pixel(map->x_pix, map->y_pix, &temp, fr);
			map->x_pix++;
		}
		map->y_pix++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, 
		temp.img_ptr, 0, 0);
	if (vars->img.img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->img.img_ptr);
	vars->img = temp;
};

void	newton_render(t_graph *fr, t_pixel *map, t_vars *vars)
{
	t_img	temp;

	temp.img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	temp.pixel_data_addr = mlx_get_data_addr(temp.img_ptr, &temp.bits_per_pixel,
				&temp.line_len, &temp.endian);
	map->y_pix = 0;
	while (map->y_pix < HEIGHT)
	{
		map->x_pix = 0;
		while (map->x_pix < WIDTH)
		{
			handle_pixel_newton(map->x_pix, map->y_pix, &temp, fr);
			map->x_pix++;
		}
		map->y_pix++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, 
		temp.img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx_ptr, vars->img.img_ptr);
	vars->img = temp;
};

void	set_xy_axis(t_graph *fr, t_vars *vars)
{
	for (int i = 0; i < WIDTH; ++i)
		put_pixel(&vars->img, i, ((HEIGHT / 2)), fr->color);
	for (int j = 0; j < HEIGHT; ++j)
		put_pixel(&vars->img, ((WIDTH / 2)), j, fr->color);
}

void	pixel_to_coord(t_pixel *map, t_graph *fr)
{
	fr->x_coord = (map->x_pix - map->x_foc) / map->pix_per_unit;
	fr->y_coord = (map->y_pix - map->y_foc) / (-1 * map->pix_per_unit);
}

void	coord_to_pixel(t_pixel *map, t_graph *fr)
{
	map->x_pix = (fr->x_coord * map->pix_per_unit) + map->x_foc;
	map->y_pix = (fr->y_coord * map->pix_per_unit) + map->y_foc;
}

// adjusts pix_per, around static focus point, based on pixel inputs
void	zoom(t_pixel *map)
{
	printf("zoom in on pixel (%f,%f)\n", map->x_pix, map->y_pix);
	
}

void	plot_image(t_graph *fr, t_pixel *map, t_vars *vars)
{
	init_pix_coord(fr, map);
	while (map->y_pix < HEIGHT)
	{
		while (map->x_pix < WIDTH)
		{
			// pixel_to_coord(map, fr);
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
