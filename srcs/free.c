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
	t_tiny_list	*tiny;

	tiny = (t_tiny_list *)(ptr - 1);
	if (!tiny->used)
		malloc_error_quit("Attempting to double free pointer");
	tiny->used = 0;
	block->active_members--;
}

void	free_small_block(t_block_zone *block, void *ptr)
{
	//
}

void	free_large_block(t_block_zone *block, void *ptr)
{
	//
}

void	free_all_blocks(void)
{
	//
}

void	free(void *ptr)
{
	t_block_data	block_data;

	block_data = find_block(ptr);
	if (block_data.block_type == TINY_BLOCK)
		free_tiny_block(block_data.block, ptr);
	else if (block_data.block_type == SMALL_BLOCK)
		free_small_block(block_data.block, ptr);
	else if (block_data.block_type == LARGE_BLOCK)
		free_large_block(block_data.block, ptr);
	else
		malloc_error_quit("Attempting to free unallocated regin");
	// else error quit, double free error.
	// find matching block, then set used to false, afterwards free it it.
}
