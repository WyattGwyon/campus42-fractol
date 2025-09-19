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
# include <stdbool.h>
# include <limits.h>

# define WIDTH 						800
# define HEIGHT 					600

typedef struct s_ctx	t_ctx;
typedef int				(*t_event)(t_ctx *ctx);
typedef int				(*t_wrapper)(int keysym, t_ctx *ctx);

typedef struct s_complex
{
	double	real;
	double	i;
}	t_complex;

typedef struct s_zoom
{
	double	x_zoom;
	double	y_zoom;
	double	x_len;
	double	y_len;
	double	to_x_min_pix;
	double	to_x_max_pix;
	double	to_y_min_pix;
	double	to_y_max_pix;
}	t_zoom;

typedef struct s_newton
{
	t_complex	z2;
	t_complex	z3;
	t_complex	fz;
	t_complex	dfz;
	t_complex	fract;
	t_complex	result;
}	t_newton;

typedef struct s_graph
{
	char	*name;
	double	x_coord;
	double	y_coord;
	double	max_x;
	double	min_x;
	double	max_y;
	double	min_y;
	double	shift_x;
	double	shift_y;
	int		max_iter;
	double	zoom;
	int		color;
	int		color_min;
	int		color_max;
	double	escape_value;
	int		iterations;
	double	julia_x;
	double	julia_y;
}	t_graph;

typedef struct s_pixel
{
	int		pix_per_unit;
	float	pix_val;
	double	zoom;
	double	x_pix;
	double	y_pix;
	int		x_foc;
	int		y_foc;
}	t_pixel;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_data_addr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_vars;

typedef struct s_color_map
{
	int	key;
	int	color_min;
	int	color_max;
}	t_color_map;

typedef struct s_event_map
{
	int		key;
	t_event	event;
}	t_event_map;

typedef struct s_wrapper_map
{
	int			key;
	t_wrapper	wrapper;
}	t_wrapper_map;

typedef struct s_ctx
{
	t_vars				vars;
	t_pixel				map;
	t_graph				fr;
	const t_color_map	*color;
	const t_event_map	*event;
	const t_wrapper_map	*wrapper;
}	t_ctx;

// events
int					move_left(t_ctx *ctx);
int					move_right(t_ctx *ctx);
int					move_up(t_ctx *ctx);
int					move_down(t_ctx *ctx);
int					iter_up(t_ctx *ctx);
int					iter_down(t_ctx *ctx);
int					reset(t_ctx *ctx);
int					color(int keysym, t_ctx *ctx);
int					shift_iterate(int keysym, t_ctx *ctx);
int					color_wrapper(int keysym, t_ctx *ctx);
int					shift_iterate_wrapper(int keysym, t_ctx *ctx);
int					wrapper_handler(int keysym, t_ctx *ctx);
int					mouse_events(int button, int x, int y, t_ctx *ctx);

// libft
int					ft_printf(const char *fmt, ...);
double				ft_atof(const char *str);
void				ft_strarr_free(char ***strarr);
void				*ft_calloc(size_t count, size_t size);
char				**ft_strarr_join(char **arr1, char **arr2);
void				ft_intarr_free(int **arr);
void				ft_struct_free(void **ptr);
void				ft_floatarr_free(double **arr);

// error & cleanup
int					cleanup(void *param);
void				malloc_error(void);
void				usage_error(char *argv[]);

// init
int					image_init(t_vars *vars, char **argv, t_graph *fr,
						t_pixel *map);
const t_color_map	*make_color_table(void);
const t_event_map	*make_event_table(void);
const t_wrapper_map	*make_wrapper_table(void);
void				init_tables(t_ctx *ctx);
void				init_pix_coord(t_graph *fr, t_pixel *map);
void				init_vars(t_vars *vars);

// fractol
void				plot_image(t_graph *fr, t_pixel *map, t_vars *vars);
double				mandel(double x);
void				put_pixel(t_img *img, int x, int y, int color);
void				set_xy_axis(t_graph *fr, t_vars *vars);
double				map(double unscaled_num, double new_min, double new_max,
						double old_max);
t_complex			sum_complex(t_complex z1, t_complex z2);
t_complex			square_complex(t_complex z);
void				fractal_render(t_graph *fr, t_pixel *map, t_vars *vars);
void				init_pix_coord(t_graph *fr, t_pixel *map);
void				handle_pixel_newton(int x, int y, t_img *img, t_graph *fr);
void				newton_render(t_graph *fr, t_pixel *map, t_vars *vars);
void				init_julia(t_ctx *ctx, char *argv[]);

// math_utils.c
t_complex			sum_complex(t_complex z1, t_complex z2);
t_complex			square_complex(t_complex z);
t_complex			multiply_complex(t_complex a, t_complex b);
t_complex			divide_complex(t_complex a, t_complex b);

// newton.c
t_complex			newton(t_complex z);
void				newton_zoom_in(t_graph *fr, double factor, int px, int py);
int					newton_event(int button, int x, int y, t_ctx *ctx);
void				handle_pixel_newton(int x, int y, t_img *img, t_graph *fr);

#endif