/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:23:35 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:40:34 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_countstart(const char *s1, const char *set)
{
	int	count;

	count = 0;
	while (s1[count] && ft_isset(s1[count], set))
		count++;
	return (count);
}

static int	ft_countend(const char *s1, const char *set)
{
	int	count;
	int	size;

	size = 0;
	count = 0;
	while (s1[size])
		size++;
	size--;
	while (size >= 0 && ft_isset(s1[size], set))
	{	
		count++;
		size--;
	}
	return (count);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		len;
	int		cstart;
	int		cend;

	len = ft_strlen(s1);
	cstart = ft_countstart(s1, set);
	cend = ft_countend(s1, set);
	if (cstart == cend && cstart == len)
		return (str = ft_calloc(1, sizeof(char)));
	str = malloc(1 + len - cstart - cend);
	if (!str)
		return (0);
	str[len - cstart - cend] = 0;
	ft_memcpy(str, s1 + cstart, len - cstart - cend);
	return (str);
}

// int	main(void)
// {
// 	char *s1 = "  \t \t \n   \n\n\n\t";
//  	char *s2 = "";
// 	printf("c : %s \n", ft_strtrim(s1," \n\t"));
// 	return (1);
// }
