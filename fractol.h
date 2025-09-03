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

# define WIDTH 1600
# define HEIGHT 1000
# define X				50
# define Y				50

// typedef struct s_img
// {
// 	void	*img_ptr;
// 	char	*img_pixels_ptr;
// 	int		bits_per_pixel;
// 	int		endian;
// 	int		line_len;
// }				t_img;

// typedef struct s_data
// {
//     void	*mlx;
//     void	*win;
// 	t_img	img;
// }               t_data;

#endif