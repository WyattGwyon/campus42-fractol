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

int cleanup(void *param)
{
	t_vars *vars= (t_vars *)param;
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->img.img_ptr);
	if (vars->win_ptr)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	if (vars->mlx_ptr)
		mlx_destroy_display(vars->mlx_ptr);
	if (vars->mlx_ptr)
		free(vars->mlx_ptr); 
	exit(0);
}