/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_small_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 09:28:57 by khansman          #+#    #+#             */
/*   Updated: 2017/06/09 09:28:58 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	divide_small_block(t_small_list *small, size_t size)
{
	t_small_list		*new_small;

	ERROR_RETURN(size > small->next + 2 + SMALL_TOLERANCE);
	new_small = (small + size) + 2;
	new_small->used = 0;
	new_small->next = small->next - (size + 2);
	small->next = size + 2;
	return (1);
}

char	merge_small_block(t_small_list *small)
{
	t_small_list		*old_small;

	old_small = small + small->next + 2;
	ERROR_RETURN(small->next + old_small->next + 2 > SMALL_MAX ||
		old_small->used);
	small->next += old_small->next + 2;
	return (1);
}

/*
** Doesn't include error halding for page overflow
*/

char	realloc_small_block(void *ptr, size_t size)
{
	t_small_list		*small;

	small = (t_small_list *)(ptr - 2);
	if (size < (size_t)small->next && size < SMALL_MAX)
	{
		SUCCESS_RETURN(size > small->next + SMALL_TOLERANCE);
		SUCCESS_RETURN(divide_small_block(small, size));
	}
	else if (size > small->next)
		SUCCESS_RETURN(merge_small_block(small));
	return (0);
}
