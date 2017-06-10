/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_small_block.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:57:37 by khansman          #+#    #+#             */
/*   Updated: 2017/06/08 16:57:40 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	compatable_small_block(t_small_list *small, size_t size)
{
	if (small->used)
		return (0);
	if (small->next)
	{
		if (small->next < size && size > (small->next + SMALL_TOLERANCE))
		{
			small->used = 1;
			return (1);
		}
	}
	else
	{		
		small->next = size + 1;
		small->used = 1;
		small += small->next;
		small->used = 0;
		small->next = 0;
		return (1);
	}
	return (0);
}

void	*scan_small_block(t_block_zone *block, size_t size)
{
	t_small_list		*small;
	size_t			distance;

	distance = sizeof(t_block_zone) + size + 2;
	small = (t_small_list *)(block + sizeof(t_block_zone) + 1);
	while (distance < (size_t)block->ps.size)
	{
		if (compatable_small_block(small, size))
			return ((void *)(small + 1));
		distance += small->next;
		small += small->next;
	}
	return (NULL);
}
