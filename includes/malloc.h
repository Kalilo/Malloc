/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 07:39:42 by khansman          #+#    #+#             */
/*   Updated: 2017/06/08 07:39:44 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** ----------\
** Includes   |
** ----------/
*/

/*
** # ifdef __APPLE__
** #  include <strings.h>
** # else
** #  include <string.h>
** # endif
*/

# include <sys/mman.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <unistd.h>
# include <pthread.h>

#include "../libft/includes/libft.h"

/*
** ----------\
** Defines    |
** ----------/
*/

/*
** Limits
*/
# define TINY_MAX 127
# define SMALL_MAX 32768

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/*
** Return Values
*/
# define FATAL_ERROR_RETURN(x) if(x)return(-1)
# define ERROR_RETURN(x) if(x)return(0)
# define SUCCESS_RETURN(x) if(x)return(1)

/*
** Flags
*/
# define MMAP_PROT PROT_READ|PROT_WRITE
# define MMAP_FLAGS MAP_ANON|MAP_PRIVATE
# define MMAP_FFLAGS MAP_ANON|MAP_PRIVATE|MAP_FIXED

/*
** Tolerance
*/
# define TINY_TOLERANCE    8
# define SMALL_TOLERANCE  16
# define LARGE_TOLERANCE  32

/*
** Types
*/
# define NO_BLOCK        0
# define TINY_BLOCK      1
# define SMALL_BLOCK     2
# define LARGE_BLOCK     3

/*
** Shorten
*/
# define BLOCK_END block->ps.size + block

/*
** ----------\
** Structures |
** ----------/
*/

/*
** Sizes
*/
typedef struct			s_page_size
{
	int					pages;
	int					size;
}						t_page_size;

/*
** Linked Lists
*/
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
	t_page_size			ps;
	int					active_members;
}						t_block_zone;

/*
** Tracking
*/
typedef struct			s_malloc_zones
{
	t_block_zone		*tiny_block;
	t_block_zone		*small_block;
	t_block_zone		*large_block;
}						t_malloc_zones;

typedef struct			s_block_data
{
	char				block_type;
	t_block_zone		*block;
}						t_block_data;

/*
** ----------\
** Globals    |
** ----------/
*/

# ifdef MAIN_FILE

t_malloc_zones			g_zones;
int						g_page_size;

# else

extern t_malloc_zones	g_zones;
extern int				g_page_size;

# endif

/*
** ----------\
** Prototypes |
** ----------/
*/

/*
** erorr_quit.c
*/
void			malloc_error_quit(char *error_message);

/*
** find_block.c
*/
char			is_in_block(t_block_zone *block, void *ptr);
t_block_data	find_in_tiny_block(void *ptr);
t_block_data	find_in_small_block(void *ptr);
t_block_data	find_in_large_block(void *ptr);
t_block_data	find_block(void *ptr);

/*
** free.c
*/
void			free_tiny_block(t_block_zone *block, void *ptr);
void			free_small_block(t_block_zone *block, void *ptr);
void			free_large_block(t_block_zone *block);
void			free_all_blocks(void);
void			free(void *ptr);

/*
** init.c
*/
void			init_memory(void);

/*
** malloc.c
*/
void			*malloc_tiny_block(size_t size);
void			*malloc_small_block(size_t size);
void			*malloc_large_block(size_t size);
void			*malloc(size_t size);

/*
** pages.c
*/
t_page_size		round_to_pagesize(int size);
void			*allocate_page(void	*start_point, size_t size);

/*
** realloc_large_block.c
*/
char			resize_large_block(t_block_zone *block, t_page_size ps);
void			*realloc_large_block(t_block_zone *block, size_t size);

/*
** realloc_small_block.c
*/
char			divide_small_block(t_small_list *small, size_t size);
char			merge_small_block(t_small_list *small);
char			realloc_small_block(void *ptr, size_t size);

/*
** realloc_tiny_block.c
*/
char			divide_tiny_block(t_tiny_list *tiny, size_t size);
char			merge_tiny_block(t_tiny_list *tiny);
char			realloc_tiny_block(void *ptr, size_t size);

/*
** scan_small_block.c
*/
char			compatable_small_block(t_small_list *small, size_t size);
void			*scan_small_block(t_block_zone *block, size_t size);

/*
** scan_tiny_block.c
*/
char			compatable_tiny_block(t_tiny_list *tiny, size_t size);
void			*scan_tiny_block(t_block_zone *block, size_t size);

/*
** zones.c
*/
char			extend_zone(t_block_zone *block, t_page_size page_size);
char			malloc_zone(size_t size, t_block_zone **start_block);

/*
** Bonus Summary:
** -> free_all_blocks
** -> double free error handling
*/

/*
**                                /----------\                                **
** ----- ----- ----- ----- ----- |  The End   | ----- ----- ----- ----- ----- **
**                                \----------/                                **
*/
#endif
