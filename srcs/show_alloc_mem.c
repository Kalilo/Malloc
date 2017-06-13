/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 08:06:10 by khansman          #+#    #+#             */
/*   Updated: 2017/06/13 08:06:14 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_print_hex_l(unsigned long num)
{
	static char *base = "0123456789ABCDEF";

	if (num >= 16)
		ft_print_hex(num / 16);
	write(1, (base + (num % 16)), 1);
}

void	show_tiny_list(t_block_zone *block)
{
	t_tiny_list		*tiny;

	tiny = (t_tiny_list *)((long)block + sizeof(t_block_zone) + 1);
	while (tiny->next)
	{
		if (tiny->used)
		{
			ft_putstr("0x");
			ft_print_hex_l((long)tiny);
			ft_putstr(" - ");
			ft_print_hex_l((long)tiny + (long)tiny->next);
			ft_putchar('\n');
		}
	}
}

void	show_small_list(t_block_zone *block)
{
	t_small_list		*small;

	small = (t_small_list *)((long)block + sizeof(t_block_zone) + 1);
	while (small->next)
	{
		if (small->used)
		{
			ft_putstr("0x");
			ft_print_hex_l((long)small);
			ft_putstr(" - ");
			ft_print_hex_l((long)small + (long)small->next);
			ft_putchar('\n');
		}
	}
}

void	show_alloc_block(t_block_zone *block, char type)
{
	while (block)
	{
		if (type == TINY_BLOCK)
			ft_putstr("TINY : 0x");
		else if (type == SMALL_BLOCK)
			ft_putstr("SMALL : 0x");
		else if (type == LARGE_BLOCK)
			ft_putstr("LARGE : 0x");
		ft_print_hex_l((long)block);
		ft_putchar('\n');
		if (type == TINY_BLOCK)
			show_tiny_list(block);
		else if (type == SMALL_BLOCK)
			show_small_list(block);
		else if (type == LARGE_BLOCK)
		{
			ft_putstr("0x");
			ft_print_hex_l((long)block + (long)sizeof(t_block_zone));
			ft_putchar('\n');
		}
		block = block->next;
	}
}

void	show_alloc_mem()
{
	t_block_zone	*block;

	block = g_zones.tiny_block;
	while (block)
	{
		show_alloc_block(block, TINY_BLOCK);
		block = block->next;
	}
	block = g_zones.small_block;
	while (block)
	{
		show_alloc_block(block, SMALL_BLOCK);
		block = block->next;
	}
	block = g_zones.large_block;
	while (block)
	{
		show_alloc_block(block, LARGE_BLOCK);
		block = block->next;
	}
}
