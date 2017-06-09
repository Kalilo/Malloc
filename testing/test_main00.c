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
	printf("Attempting To malloc, and free 12bytes:\n");
	void	*test00 = malloc(12);
	free(test00);
	printf("\tSucess!\n");
}
