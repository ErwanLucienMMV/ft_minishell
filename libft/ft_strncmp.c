/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:51:01 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:21:30 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	if (size == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < size - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(void)
// {
// 	char *s1 = "abcdefg";
// 	char *s2 = "abcdh";
// 	printf("Pour 5 char : %d \n", ft_strncmp(s1, s2, 5));
// 	printf("Pour 4 char : %d \n", ft_strncmp(s1, s2, 4));
// 	return (1);
// }