/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:30:25 by clouden           #+#    #+#             */
/*   Updated: 2025/09/01 20:30:28 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minilibx-linux/mlx.h"

int main(void)
{
	void *mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);

	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}