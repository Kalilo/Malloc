/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t01.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 09:25:01 by khansman          #+#    #+#             */
/*   Updated: 2017/06/08 09:25:03 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/mman.h>

# include "../libft/includes/libft.h"

# define TINY_MAX 127
# define SMALL_MAX 32768

typedef struct			s_tiny_list
{
	unsigned char		used : 1;
	unsigned char		next : 7;
}						t_tiny_list;

typedef struct			s_small_list
{
	unsigned short		used : 1;
	unsigned short		next : 15;
}						t_small_list;

typedef struct			s_page_size
{
	int							pages;
	int							size;
}						t_page_size;

typedef struct			s_block_zone
{
	struct s_block_zone	*next;
	t_page_size			ps;
}						t_block_zone;

typedef struct			s_malloc_zones
{
	t_block_zone		*tiny_block;
	t_block_zone		*small_block;
	t_block_zone		*large_block;
}						t_malloc_zones;

t_malloc_zones			g_zones;
int						g_page_size;

void	init_memory(void) {
	ft_bzero(&g_zones, sizeof(t_malloc_zones));
	g_page_size = getpagesize();
}

t_page_size	round_to_pagesize(int size)
{
	t_page_size		ps;

	ps.size = g_page_size;
	ps.pages = 1;
	while (ps.size < size && ps.size && ps.pages++)
		ps.size += g_page_size;
	if (!ps.size)
		ps.pages = -1;
	return (ps);
}

void	*allocate_page(void	*start_point, size_t size)
{
	void	*address;

	if (start_point == NULL)
		address = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		address = mmap(start_point, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE |  MAP_FIXED, -1, 0);
	
	return (address);
}

char	malloc_zone(size_t size, t_block_zone **start_block)
{
	t_block_zone	*block;
	t_page_size		page_size;

	page_size = round_to_pagesize(size);
	if (!page_size.pages)
		return (0);
	block = *start_block;
	if (block)
	{
		while (block && block->next)
			block = block->next;
		block->next = allocate_page(NULL, page_size.size);//still need to account for increasiong the page size
		if (!block->next)
			return (-1);
		block = block->next
	}
	else
	{
		*start_block = allocate_page(NULL, page_size.size);//also needs to handle alternative case
		if (!start_block)
			return (-1);
	}
	block.ps = page_size;
	return (1);
}

// char	malloc_small_zone(size_t size)
// {
// 	if (g_zones.small_block == NULL)
// 		g_zones.small_block = allocate_page(NULL, 2 * g_page_size);
// 	if (g_zones.small_block == NULL)
// 		return (0);
// 	return (1);
// }
