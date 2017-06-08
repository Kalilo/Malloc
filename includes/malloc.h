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

/*
** ----------\
** Defines    |
** ----------/
*/

/*
** ----------\
** Structures |
** ----------/
*/

/*
** ----------\
** Globals    |
** ----------/
*/

/*
** ----------\
** Prototypes |
** ----------/
*/

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);

#endif
