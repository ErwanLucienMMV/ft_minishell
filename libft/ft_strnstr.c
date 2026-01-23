/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:08:34 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:22:07 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *bigstr, const char *littlestr, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(littlestr);
	if (!littlestr[i])
		return ((char *)bigstr);
	while (bigstr[i] && i < len)
	{
		j = 0;
		while (bigstr[i + j] == littlestr[j] && littlestr[j] && i + j < len)
			j++;
		if (j == little_len)
			return ((char *)bigstr + i);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char *s1 = "lorem ipsum dolor sit amet";
//  	char *s2 = "dolor";
//  	int max = strlen(s1);
// 	char *i2 = ft_strnstr(s1, s2, 0);
// 	printf("%s \n", ft_strnstr(s1, s2, 0));
// 	return (1);
// }
