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
	t_block_zone	*block;
	t_block_zone	*parent_block;
	void			*zone;

	block = g_zones.tiny_block;
	parent_block = block;
	while (block)
	{
		if ((zone = scan_tiny_block) != NULL && ++block->active_members)
			return (zone);
		parent_block = block;
		block = block->next;
	}
	ERROR_RETURN(!malloc_zone(size, &block));
	if (parent_block == NULL)
		g_zones.tiny_block = block;
	else
		parent_block->next = block;
	if ((zone = scan_tiny_block) != NULL && ++block->active_members)
		return (zone);
	return (NULL);
}

void		*malloc_small_block(size_t size)
{
	t_block_zone	*block;
	t_block_zone	*parent_block;
	void			*zone;

	block = g_zones.small_block;
	parent_block = block;
	while (block)
	{
		if ((zone = scan_small_block) != NULL && ++block->active_members)
			return (zone);
		parent_block = block;
		block = block->next;
	}
	ERROR_RETURN(!malloc_zone(size, &block));
	if (parent_block == NULL)
		g_zones.small_block = block;
	else
		parent_block->next = block;
	if ((zone = scan_small_block) != NULL && ++block->active_members)
		return (zone);
	return (NULL);
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
	init_memory();
	if (size < TINY_MAX)
		return (malloc_tiny_block(size));
	if (size < SMALL_MAX)
		return (malloc_small_block(size));
	return (malloc_large_block(size));
}
