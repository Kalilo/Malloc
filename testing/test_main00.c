/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:54:17 by khansman          #+#    #+#             */
/*   Updated: 2017/06/09 10:54:21 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

int	main()
{
	printf("Attempting To malloc, and free 12 bytes:\n");
	void	*test00 = malloc(12);
	free(test00);
	printf("\tSucess!\n");
	printf("Attempting To malloc, and free 10 * 32 bytes:\n");
	void	*test01[10];
	for (int k = 0; k < 10; k++) {
		test01[k] = malloc(32);
		printf("allocated test01[%d]: %p\n", k, test01[k]);
	}
	for (int k = 0; k < 10; k++) {
		printf("freeing test01[%d]: %p\n", k, test01[k]);
		free(test01[k]);
	}
	printf("\tSucess!\n");

	free(NULL);
}
