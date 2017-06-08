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

# define TINY_MAX 127
# define SMALL_MAX 32768

typedef struct			s_small_list
{
	char				used : 1;
	char				next : 7;
}						t_small_list;

typedef struct			s_block_zone
{
	struct s_block_zone	*next;
	unsigned char		pages;
}						t_block_zone;

typedef struct			s_malloc_zones
{
	void				*tiny_block;
	void				*small_block;
	void				*large_block;
}						t_malloc_zones;

// char	init_memory(void) {

// }
