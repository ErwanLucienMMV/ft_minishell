/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:22:29 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:21:21 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>
#include <stdio.h>

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	src_len = 0;
	while (src[src_len])
	{
		if (dest_len < size - 1 && size > 0)
		{
			dst[dest_len] = src[dest_len];
			dest_len++;
		}
		src_len++;
	}
	if (size != 0)
		dst[dest_len] = 0;
	return (src_len);
}

// int	main(void)
// {
// 	char *str = "hello !";
// 	char buff1[0xF00];
// 	char buff2[0xF00];
// 	int r1;
// 	int r2;

// 	memset(buff1, 'A', 20);
// 	memset(buff2, 'A', 20);
// 	r1 = strlcpy(buff1, str, 2);
// 	r2 = ft_strlcpy(buff2, str, 2);
// 	printf("%d %d \n", r1, r2);
// }
