/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:00:46 by clouden           #+#    #+#             */
/*   Updated: 2025/09/14 20:00:49 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real + z2.real;
	result.i = z1.i + z2.i;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.i * z.i);
	result.i = (2 * z.real * z.i);
	return (result);
}

t_complex	multiply_complex(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real * b.real) - (a.i * b.i);
	result.i = (a.real * b.i) + (a.i * b.real);
	return (result);
}

t_complex	divide_complex(t_complex a, t_complex b)
{
	t_complex	result;
	double		denom;

	denom = (b.real * b.real) + (b.i * b.i);
	result.real = (a.real * b.real) + (a.i * b.i) / denom;
	result.i = (a.real * b.i) - (a.i * b.real) / denom;
	return (result);
}

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return (((new_max - new_min) * (unscaled_num / old_max)) + new_min);
}
