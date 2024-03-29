/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 07:53:04 by khansman          #+#    #+#             */
/*   Updated: 2016/12/03 07:53:06 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	k;
	char	*temp;

	k = 0;
	temp = (char *)s;
	while (k < n)
	{
		temp[k] = '\0';
		k++;
	}
}
