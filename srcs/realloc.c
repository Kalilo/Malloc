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

char	realloc_tiny_block(void *ptr, size_t size)
{
	t_tiny_list		*tiny;

	tiny = (t_tiny_list *)(ptr - 1);
	if (size < (size_t)tiny->next && size < TINY_MAX)
	{
		SUCCESS_RETURN(size > tiny->next + TINY_TOLERANCE);
		// Case handle dividing a block
	}
	// Case handle merging blocks
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	t_block_data	block_data;

	// find block, attempt to resize or malloc new block
	block_data = find_block(ptr);
	//
	return (NULL);
}
