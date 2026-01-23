/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:49:16 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:31:42 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// size_t	ft_strlen(const char *c)
// {
// 	int	i;

// 	i = 0;
// 	while (c[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (start > ft_strlen(s))
	{
		substr = malloc(1);
		if (!substr)
			return (0);
		substr[0] = 0;
		return (substr);
	}
	if (ft_strlen(s + start) < len)
		substr = malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	i = start;
	j = 0;
	while (s[i] && j < len)
		substr[j++] = s[i++];
	substr[j] = 0;
	return (substr);
}

// int main(void)
// {
// 	printf("%s \n", ft_substr("hola", 0, 18446744073709551615));
// 	return (1);
// }
