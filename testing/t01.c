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

typedef struct			s_block_zone
{
	struct s_block_zone	*next;
	unsigned char		pages;
}						t_block_zone;

typedef struct			s_malloc_zones
{
	t_block_zone		*tiny_block;
	t_block_zone		*small_block;
	t_block_zone		*large_block;
}						t_malloc_zones;

t_malloc_zones			g_zones;

void	init_memory(void) {
	ft_bzero(&g_zones, sizeof(t_malloc_zones));
}

char	malloc_small_zone(size_t size)
{
	if (g_zones.small_block == NULL)

}
