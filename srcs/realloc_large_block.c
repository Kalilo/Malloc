/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_large_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 09:29:04 by khansman          #+#    #+#             */
/*   Updated: 2017/06/09 09:29:06 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	resize_large_block(t_block_zone *block, size_t size, t_page_size ps)
{
	if (allocate_page(block, ps.size))
	{
		block->ps = ps;
		return (1);
	}
	return (0);
}

void	*realloc_large_block(t_block_zone *block, size_t size)
{
	t_page_size		ps;
	t_block_zone	*parent_block;
	t_block_zone	*new_block;

	ps = round_to_pagesize(size + sizeof(t_block_zone));
	if (ps.pages == block->ps.pages || resize_large_block(block, size, ps))
		return (block);
	parent_block = g_zones.large_block;
	while (parent_block->next && parent_block->next != block)
		parent_block = parent_block->next;
	if ((new_block = allocate_page(NULL, ps.size)) == NULL)
		return (NULL);
	new_block->next = block->next;
	new_block->ps = ps;
	parent_block->next = new_block;
	munmap(block, block->ps.size);
	return (NULL);
}