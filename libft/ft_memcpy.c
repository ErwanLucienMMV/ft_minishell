/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:46:43 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:16:26 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*s;
	unsigned char		*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (dest);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char buffer1[5] = "BBBBB";
// 	char *buffer2 = malloc(5);
//     printf("dest : %s \n", buffer2);
// 	ft_memcpy(((void*)0), ((void*)0), 3);
// 	printf("src : %s \n", buffer1);
//     printf("dest : %s \n", buffer2);
// }