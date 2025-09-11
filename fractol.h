/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:20:59 by clouden           #+#    #+#             */
/*   Updated: 2025/09/03 16:21:02 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <signal.h>
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 						1600
# define HEIGHT 					1000
# define X							50
# define Y							50
// # define MLX_SYNC_IMAGE_WRITABLE 	1
// # define MLX_SYNC_WIN_FLUSH_CMD		2
// # define MLX_SYNC_WIN_CMD_COMPLETED	3

typedef struct s_fract
{
	double	x_coord;
	double	y_coord;
	int		max_iter;
	int		color;
	double	offset_x;
	double	offset_y;
}   t_fract;

typedef struct s_map
{
	int		pix_per_unit;
	float	pix_val;
	double	zoom;
	double	x_pix;
	double	y_pix;
	int		x_foc;
	int		y_foc;
}  t_map;

// typedef struct s_fractal
// {

// }

typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_data_addr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_vars
{
    void	*mlx_ptr;
    void	*win_ptr;
	int		color;
	t_img	img;
	t_fract	fr;
}               t_vars;

int 	cleanup(void *param);
void	plot_image(t_fract *fr, t_map *map, t_vars *vars);
double	mandel(int x);
void	put_pixel(t_img *img, int x, int y, int color);
void	set_xy_axis(t_vars *vars);

#endif