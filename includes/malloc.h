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
# define SUCCESS_RETURN(X) if(x)return(1)

/*
** Flags
*/
# define MMAP_PROT PROT_READ|PROT_WRITE
# define MMAP_FLAGS MAP_ANON|MAP_PRIVATE
# define MMAP_FFLAGS MAP_ANON|MAP_PRIVATE|MAP_FIXED

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
	int							pages;
	int							size;
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

/*
** ----------\
** Globals    |
** ----------/
*/

# ifdef MAIN_FILE

t_malloc_zones			g_zones;
int						g_page_size;

else

extern t_malloc_zones	g_zones;
extern int				g_page_size;

# endif

/*
** ----------\
** Prototypes |
** ----------/
*/

/*
** Todo
*/
void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);

/*
** init.c
*/
void		init_memory(void);

/*
** pages.c
*/
t_page_size	round_to_pagesize(int size);
void		*allocate_page(void	*start_point, size_t size);

/*
** zones.c
*/
char		extend_zone(t_block_zone *block, t_page_size page_size);
char		malloc_zone(size_t size, t_block_zone **start_block);

/*
**                                /----------\                                **
** ----- ----- ----- ----- ----- |  The End   | ----- ----- ----- ----- ----- **
**                                \----------/                                **
*/
#endif
