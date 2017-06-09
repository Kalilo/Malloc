/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 07:38:29 by khansman          #+#    #+#             */
/*   Updated: 2017/06/09 07:38:30 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_tiny_block(t_block_zone *block, void *ptr)
{
	t_tiny_list		*tiny;
	t_block_zone	*parent_block;

	tiny = (t_tiny_list *)(ptr - 1);
	if (!tiny->used)
		malloc_error_quit("Attempting to double free pointer");
	tiny->used = 0;
	block->active_members--;
	if (!block->active_members && block != g_zones.tiny_block)
	{
		parent_block = g_zones.tiny_block;
		while (parent_block && parent_block->next != block)
			parent_block = parent_block->next;
		if (parent_block->next == block)
		{
			parent_block->next = block->next;
			munmap(block, block->ps.size);
		}
	}
}

void	free_small_block(t_block_zone *block, void *ptr)
{
	t_small_list		*small;
	t_block_zone	*parent_block;

	small = (t_small_list *)(ptr - 2);
	if (!small->used)
		malloc_error_quit("Attempting to double free pointer");
	small->used = 0;
	block->active_members--;
	if (!block->active_members && block != g_zones.small_block)
	{
		parent_block = g_zones.small_block;
		while (parent_block && parent_block->next != block)
			parent_block = parent_block->next;
		if (parent_block->next == block)
		{
			parent_block->next =block->next;
			munmap(block, block->ps.size);
		}
	}
}

void	free_large_block(t_block_zone *block)
{
	t_block_zone	*parent_block;

	parent_block = g_zones.large_block;
	while (parent_block && parent_block->next != block)
		parent_block = parent_block->next;
	if (parent_block->next == block)
	{
		parent_block->next = block->next;
		munmap(block, block->ps.size);
	}
}

void	free_all_blocks(void)
{
	t_block_zone	*block;

	block = g_zones.tiny_block;
	while (block && munmap(block, block->ps.size) + 1)
		block = block->next;
	block = g_zones.small_block;
	while (block && munmap(block, block->ps.size) + 1)
		block = block->next;
	block = g_zones.large_block;
	while (block && munmap(block, block->ps.size) + 1)
		block = block->next;
}

void	free(void *ptr)
{
	t_block_data	block_data;

	init_memory();
	if (ptr == NULL)
	{
		free_all_blocks();
		return ;
	}
	block_data = find_block(ptr);
	if (block_data.block_type == TINY_BLOCK)
		free_tiny_block(block_data.block, ptr);
	else if (block_data.block_type == SMALL_BLOCK)
		free_small_block(block_data.block, ptr);
	else if (block_data.block_type == LARGE_BLOCK)
		free_large_block(block_data.block);
	else
		malloc_error_quit("Attempting to free unallocated regin");
}
