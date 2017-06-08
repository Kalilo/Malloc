/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t00.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 08:24:55 by khansman          #+#    #+#             */
/*   Updated: 2017/06/08 08:24:56 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/mman.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <unistd.h>
# include <pthread.h>

#include <stdio.h>

int		main() {
	printf("Page Size: %d\n", getpagesize());
}
