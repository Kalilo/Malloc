/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:57:43 by khansman          #+#    #+#             */
/*   Updated: 2017/06/08 15:57:45 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAIN_FILE
#include "../includes/malloc.h"

void		*malloc_tiny_block(size_t size)
{
	//
}

void		*malloc_small_block(size_t size)
{
	//
}

void		*malloc_large_block(size_t size)
{
	t_block_zone	*block;

	if (!malloc_zone(size, &g_zones.large_block))
		return (NULL);
	block = g_zones.large_block;
	while (block->next)
		block = block->next;
	block->active_members = 1;
	return ((void *)(block + sizeof(t_block_zone)));
}

void		*malloc(size_t size)
{
	if (size < TINY_MAX)
		return (malloc_tiny_block(size));
	else if (size < SMALL_MAX)
		return (malloc_small_block(size));
	else
		return (malloc_large_block(size));
}
