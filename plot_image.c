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
	return ;
}

void	calculate_fractol(t_graph *fr, t_complex *z, t_complex *c)
{
	t_complex	tmp;

	if (!ft_strncmp(fr->name, "mandelbrot", 10) || \
		!ft_strncmp(fr->name, "julia", 5))
		*z = sum_complex(square_complex(*z), *c);
	else if (!ft_strncmp(fr->name, "burningship", 11))
	{
		tmp.real = fabs(z->real);
		tmp.i = fabs(z->i);
		*z = sum_complex(square_complex(tmp), *c);
	}
	else if (!ft_strncmp(fr->name, "celtic", 6))
	{
		tmp.real = z->real * z->real - z->i * z->i;
		tmp.i = 2 * z->real * z->i;
		z->real = fabs(tmp.real) + c->real;
		z->i = tmp.i + c->i;
	}
	else if (!ft_strncmp(fr->name, "tricorn", 7))
	{
		tmp.real = z->real * z->real - z->i * z->i + c->real;
		tmp.i = -2 * z->real * z->i + c->i;
		z->real = tmp.real;
		z->i = tmp.i;
	}
}

void	handle_pixel(int x, int y, t_img *img, t_graph *fr)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	z.real = map(x, fr->min_x, fr->max_x, WIDTH) + fr->shift_x;
	z.i = map(y, fr->min_y, fr->max_y, HEIGHT) + fr->shift_y;
	mandel_or_julia(&z, &c, fr);
	while (i < fr->iterations)
	{
		calculate_fractol(fr, &z, &c);
		if ((z.real * z.real) + (z.i * z.i) > fr->escape_value)
		{
			fr->color = map(i, fr->color_max, fr->color_min, fr->iterations);
			put_pixel(img, x, y, fr->color);
			return ;
		}
		i++;
	}
	put_pixel(img, x, y, 0x000000);
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
}

// void	fractal_render(t_graph *fr, t_pixel *map, t_vars *vars)
// {
// 	map->y_pix = 0;
// 	while (map->y_pix < HEIGHT)
// 	{
// 		map->x_pix = 0;
// 		while (map->x_pix < WIDTH)
// 		{
// 			handle_pixel(map->x_pix, map->y_pix, &vars->img, fr);
// 			map->x_pix++;
// 		}
// 		map->y_pix++;
// 	}
// 	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
// 		vars->img.img_ptr, 0, 0);
// }