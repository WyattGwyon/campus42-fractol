/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:53:05 by clouden           #+#    #+#             */
/*   Updated: 2025/09/11 17:53:08 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

void	usage_error(char *argv[])
{
	ft_printf(
		"fractol: usage: Please enter:\n\t\"%s mandelbrot\" or\n"
		"\t\"%s julia <float_1> <float_2>\"\n", argv[0], argv[0]);
	exit(EXIT_FAILURE);
}

int	cleanup(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (vars->img.img_ptr)
	{
		mlx_destroy_image(vars->mlx_ptr, vars->img.img_ptr);
		vars->img.img_ptr = NULL;
	}
	if (vars->win_ptr)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		vars->win_ptr = NULL;
	}
	if (vars->mlx_ptr)
	{
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		vars->mlx_ptr = NULL;
	}
	exit(0);
}
