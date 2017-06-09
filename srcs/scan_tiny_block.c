/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tiny_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:29:23 by khansman          #+#    #+#             */
/*   Updated: 2017/06/08 16:29:25 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	compatable_tiny_block(t_tiny_list *tiny, size_t size)
{
	if (tiny->used)
		return (0);
	if (tiny->next)
	{
		if (tiny->next < size && size > tiny->next + TINY_TOLERANCE)
			return (1);
	}
	else
	{
		tiny->next = size + 1;
		tiny += tiny->next;
		tiny->used = 1;
		tiny->next = 0;
		return (1);
	}
	return (0);
}

void	*scan_tiny_block(t_block_zone *block, size_t size)
{
	t_tiny_list		*tiny;
	size_t			distance;

	distance = sizeof(t_block_zone) + size + 2;
	tiny = (t_tiny_list *)(block + distance);
	while (distance < (size_t)block->ps.size)
	{
		if (compatable_tiny_block(tiny, size))
			return ((void *)(tiny + 1));
		distance += tiny->next;
		tiny += tiny->next;
	}
	return (NULL);
}
