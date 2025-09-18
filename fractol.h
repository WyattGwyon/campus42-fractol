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

typedef struct s_parser
{
	char	**strarr;
	double	*intarr;
	int		len;
	int		max;
	int		min;
}	t_parser;

typedef struct s_complex
{
	double	real;
	double	i;
}	t_complex;

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

typedef struct s_ctx
{
	t_vars	vars;
	t_pixel	map;
	t_graph	fr;
}	t_ctx;

typedef int	(*t_event)(t_ctx *ctx);

typedef struct s_event_map
{
	int		key;
	t_event	event;
}	t_event_map;

typedef int	(*t_wrapper)(int keysym, t_ctx *ctx);

typedef struct s_wrapper_map
{
	int			key;
	t_wrapper	wrapper;
}	t_wrapper_map;

int			move_left(t_ctx *ctx);
int			move_right(t_ctx *ctx);
int			move_up(t_ctx *ctx);
int			move_down(t_ctx *ctx);
int			iter_up(t_ctx *ctx);
int			iter_down(t_ctx *ctx);
int			reset(t_ctx *ctx);
int			color(int keysym, t_ctx *ctx);
int			shift_iterate(int keysym, t_ctx *ctx);
int			color_wrapper(int keysym, t_ctx *ctx);
int			shift_iterate_wrapper(int keysym, t_ctx *ctx);
int			wrapper_handler(int keysym, t_ctx *ctx);
int			button_press(int button, int x, int y, t_ctx *ctx);

typedef struct s_color_map
{
	int	key;
	int	color_min;
	int	color_max;
}	t_color_map;

static inline const t_color_map	*gcolor_table(void)
{
	static const t_color_map	color_table[] = {
	{XK_1, 0x00ff00, 0x000000},
	{XK_2, 0x0000ff, 0x000000},
	{XK_3, 0xff0000, 0xfff900},
	{XK_4, 0xff7f00, 0xffffff},
	{XK_5, 0xffff00, 0xff0000},
	{XK_6, 0x556699, 0x009999},
	{XK_7, 0xff0000, 0xff00ff},
	{XK_8, 0x001f3f, 0x0074D9},
	{XK_9, 0x886666, 0x000000},
	{XK_0, 0xffffff, 0x77ff77},
	{XK_d, 0xf00000, 0x00000f},
	{0, 0, 0}
	};

	return (color_table);
}

static inline const t_color_map	*gctable(void)
{
	static const t_color_map	*retrieve_ctable = NULL;

	if (!retrieve_ctable)
		retrieve_ctable = gcolor_table();
	return (retrieve_ctable);
}

// static inline const t_color_map *gctable(void)
// {
//     static const t_color_map *retrieve_ctable = NULL;

//     if (!retrieve_ctable)
//         retrieve_ctable = gcolor_table();

//     return (retrieve_ctable);
// }

static inline const t_event_map	*gevent_table(void)
{
	static const t_event_map	event_table[] = { 
	{XK_Up, move_up},
	{XK_Down, move_down},
	{XK_Left, move_left},
	{XK_Right, move_right},
	{XK_l, iter_down},
	{XK_h, iter_up},
	{XK_r, reset},
	{0, NULL}
	};

	return (event_table);
}

static inline const t_event_map	*getable(void)
{
	static const t_event_map	*retrieve_etable = NULL;

	if (!retrieve_etable)
		retrieve_etable = gevent_table();
	return (retrieve_etable);
}

static inline const t_wrapper_map	*gwrapper_table(void)
{
	static const t_wrapper_map	wrapper_table[] = {
	{XK_1, color_wrapper},
	{XK_2, color_wrapper},
	{XK_3, color_wrapper},
	{XK_4, color_wrapper},
	{XK_5, color_wrapper},
	{XK_6, color_wrapper},
	{XK_7, color_wrapper},
	{XK_8, color_wrapper},
	{XK_9, color_wrapper},
	{XK_0, color_wrapper},
	{XK_Up, shift_iterate_wrapper},
	{XK_Down, shift_iterate_wrapper},
	{XK_Left, shift_iterate_wrapper},
	{XK_Right, shift_iterate_wrapper},
	{XK_l, shift_iterate_wrapper},
	{XK_h, shift_iterate_wrapper},
	{XK_r, shift_iterate_wrapper},
	{0, NULL}
	};

	return (wrapper_table);
}

static inline const t_wrapper_map	*gwtable(void)
{
	static const t_wrapper_map	*retrieve_wtable = NULL;

	if (!retrieve_wtable)
		retrieve_wtable = gwrapper_table();
	return (retrieve_wtable);
}

// libft
int			ft_printf(const char *fmt, ...);
double		ft_atof(const char *str);
void		ft_strarr_free(char ***strarr);
void		*ft_calloc(size_t count, size_t size);
char		**ft_strarr_join(char **arr1, char **arr2);
void		ft_intarr_free(int **arr);
void		ft_struct_free(void **ptr);
void		ft_floatarr_free(double **arr);

// error & cleanup
void		clean_parser(t_parser **p);
int			cleanup(void *param);
void		malloc_error(void);

// init
int			image_init(t_vars *vars, char **argv, t_graph *fr, t_pixel *map);

// fractol
void		plot_image(t_graph *fr, t_pixel *map, t_vars *vars);
double		mandel(double x);
void		put_pixel(t_img *img, int x, int y, int color);
void		set_xy_axis(t_graph *fr, t_vars *vars);
t_parser	*parse_controller(int argc, char *argv[]);
double		map(double unscaled_num, double new_min, double new_max,
				double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
void		fractal_render(t_graph *fr, t_pixel *map, t_vars *vars);
void		init_pix_coord(t_graph *fr, t_pixel *map);
void		handle_pixel_newton(int x, int y, t_img *img, t_graph *fr);
void		newton_render(t_graph *fr, t_pixel *map, t_vars *vars);

t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
t_complex	multiply_complex(t_complex a, t_complex b);
t_complex	divide_complex(t_complex a, t_complex b);

t_complex	newton(t_complex z);
void		newton_zoom_in(t_graph *fr, double factor, int px, int py);
int			newton_event(int button, int x, int y, t_ctx *ctx);
void		handle_pixel_newton(int x, int y, t_img *img, t_graph *fr);

#endif