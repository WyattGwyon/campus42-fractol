/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:28:05 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 18:01:55 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
		return (malloc(0));
	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	while (i < (count * size))
	{
		((unsigned char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}
