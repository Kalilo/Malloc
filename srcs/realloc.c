/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 08:48:21 by khansman          #+#    #+#             */
/*   Updated: 2017/06/09 08:48:22 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_block_data	block_data;

	block_data = find_block(ptr);
	if (block_data.block_type == TINY_BLOCK && size <= TINY_MAX &&
			realloc_tiny_block(ptr, size))
		return (ptr);
	if (block_data.block_type == SMALL_BLOCK && size <= SMALL_MAX &&
			realloc_small_block(ptr, size))
		return (ptr);
	if (block_data.block_type == LARGE_BLOCK)
		return (realloc_large_block(ptr, size));
	free(ptr);
	return (malloc(size));
}
