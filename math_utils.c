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
	t_complex result;

	result.real = z1.real + z2.real;
	result.i = z1.i + z2.i;
	return (result);
}

t_complex square_complex(t_complex z)
{
	t_complex result;

	result.real = (z.real * z.real) - (z.i * z.i); 
	result.i = (2 * z.real * z.i);
	return (result);
}

t_complex multiply_complex(t_complex a, t_complex b)
{
	t_complex result;

	result.real = (a.real * b.real) - (a.i * b.i);
	result.i = (a.real * b.i) + (a.i * b.real);
	return (result);
}

t_complex divide_complex(t_complex a, t_complex b)
{
	t_complex result;
	double denom;

	denom = (b.real * b.real) + (b.i * b.i);
	result.real = (a.real * b.real) + (a.i * b.i) / denom;
	result.i = (a.real * b.i) - (a.i * b.real) / denom;
	return (result);
}

t_complex	newton(t_complex z)
{
	t_complex	result;
	t_newton	newt;

	newt.z2 = multiply_complex(z, z);
	newt.z3 = multiply_complex(newt.z2, z);
	newt.fz.real = newt.z3.real - 1;
	newt.fz.i = newt.z3.i;
	newt.dfz.real = 3 * newt.z2.real;
	newt.dfz.i = 3 * newt.z2.i;
	newt.fract = divide_complex(newt.fz, newt.dfz);
	result.real = z.real - newt.fract.real;
	result.i = z.i - newt.fract.i;
	return (result);
} 
void newton_zoom_in(t_graph *fr, double factor, int px, int py)
{
    double center_x = fr->min_x + px * (fr->max_x - fr->min_x) / WIDTH;
    double center_y = fr->min_y + py * (fr->max_y - fr->min_y) / HEIGHT;
    double width  = (fr->max_x - fr->min_x) * factor;
    double height = (fr->max_y - fr->min_y) * factor;

    fr->min_x = center_x - width/2;
    fr->max_x = center_x + width/2;
    fr->min_y = center_y - height/2;
    fr->max_y = center_y + height/2;
}

int     newton_event(int button, int x, int y, t_ctx *ctx)
{
	if (button == 4)
	{
		ctx->fr.iterations += 4;
		newton_zoom_in(&ctx->fr, 0.40, x, y);
		printf("x_max = %f x_min = %f\n", ctx->fr.max_x, ctx->fr.min_x);
		printf("Zoom in scroll at (%d, %d)!\n", x, y);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}
	else if (button == 5)
    {
		ctx->fr.iterations -= 2;
		// newton_zoom_out(ctx, 0.20, x, y);
		printf("Zoom out scroll at (%d, %d)!\n", x, y);
		fractal_render(&ctx->fr, &ctx->map, &ctx->vars);
	}

    return (0);
}

void handle_pixel_newton(int x, int y, t_img *img, t_graph *fr)
{
    t_complex z;
    int i;
    double tolerance = 1;

    // Map pixel to initial z0
    z.real = fr->min_x + x * (fr->max_x - fr->min_x) / WIDTH;
	z.i    = fr->min_y + y * (fr->max_y - fr->min_y) / HEIGHT;
	double roots[3][2] = {
		{1.0, 0.0},
		{-0.5,  sqrt(3)/2},
		{-0.5, -sqrt(3)/2}
	};

	for (i = 0; i < fr->iterations; i++)
	{
		z = newton(z);

		for (int r = 0; r < 3; r++)
		{
			double dx = z.real - roots[r][0];
			double dy = z.i - roots[r][1];
			if (dx*dx + dy*dy < tolerance*tolerance)
			{
				int color = (r == 0) ? 0xFF0000 : (r == 1) ? 0x00FF00 : 0x0000FF;
				put_pixel(img, x, y, color + i * 200);
				return;
			}
		}
	}
	put_pixel(img, x, y, 0x000000);
}