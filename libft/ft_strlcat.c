/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:11:40 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:20:32 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	i = 0;
	len_src = 0;
	len_dst = 0;
	while (src[len_src])
		len_src++;
	while (dst[len_dst] && len_dst < size)
		len_dst++;
	if (size - len_dst == 0)
		return (len_dst + len_src);
	while (src[i] && size - len_dst - i != 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = 0;
	return (len_src + len_dst);
}

// int	main(void)
// {
// 	int r2;
// 	char s2[4] = "";
// 	r2 = ft_strlcat(s2, "thx to ntoniolo for this test !", 4);
// 	printf("%d\n", r2);
// }
