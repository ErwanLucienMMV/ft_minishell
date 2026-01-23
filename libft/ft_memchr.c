/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:07:38 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:06:47 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t count)
{
	unsigned char	*s;

	s = (unsigned char *)src;
	while (s < (unsigned char *)src + count)
	{
		if (*s == (unsigned char)c)
			return (s);
		s++;
	}
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	char *src = "/|\x12\xff\x09\x42\2002\42|\\";
// 	printf("%s \n", ft_memchr(src, '\200', 10));
// 	printf("%s \n", memchr(src, '\200', 10));
// 	return 0;
// }
