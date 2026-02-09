/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:58:10 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/09 13:01:33 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > ((size_t) -1 / size))
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * count);
	return (ptr);
}

// int	main(void)
// {
// 	int size = 1;
//  	void * d1 = ft_calloc(size, sizeof(int));
//  	void * d2 = calloc(size, sizeof(int));
// 	if (memcmp(d1, d2, size * sizeof(int)))
// 		printf("Cc");
// 	printf("%s \n", d1);
// 	printf("%s \n", d2);
// 	return (1);
// }