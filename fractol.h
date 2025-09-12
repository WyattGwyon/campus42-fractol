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

# define WIDTH 						1000
# define HEIGHT 					600

// typedef void  (*t_operation)(t_map *map, t_fract *fr);

// typedef enum
// {
//     OP_ZOOM,
//     OP_SHIFT_HORZ,
//     OP_SHIFT_VERT,
//     OP_COUNT
// } t_op_type;

// t_operation operations[OP_COUNT] =
// {
// 	zoom,
// 	horizontal_shift,
// 	vertical_shift
// };

typedef struct s_complex
{
	double real;
	double i;
}	t_complex;

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
double	mandel(double x);
void	put_pixel(t_img *img, int x, int y, int color);
void	set_xy_axis(t_fract *fr, t_vars *vars);

#endif