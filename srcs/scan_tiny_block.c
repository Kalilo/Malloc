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
		if (tiny->next < size && size > (tiny->next + TINY_TOLERANCE))
			return (tiny->used = 1);
	}
	else
	{		
		tiny->next = size + sizeof(t_tiny_list);
		tiny->used = 1;
		tiny += tiny->next;
		tiny->used = 0;
		tiny->next = 0;
		return (1);
	}
	return (0);
}

void	*scan_tiny_block(t_block_zone *block, size_t size)
{
	t_tiny_list		*tiny;
	size_t			distance;

	distance = sizeof(t_block_zone) + size + TINY_TOLERANCE;
	tiny = (t_tiny_list *)(block + sizeof(t_block_zone) + 1);
	while (distance < (size_t)block->ps.size)
	{
		if (compatable_tiny_block(tiny, size))
			return ((void *)(tiny + sizeof(t_tiny_list)));
		distance += tiny->next;
		tiny += tiny->next;
	}
	return (NULL);
}
