/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:09:52 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 20:47:53 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_str_add_array(const char *s, int size, char *tab)
{
	int		i;

	i = 0;
	while (s[i] && i < size)
		i++;
	tab = malloc((i + 1) * sizeof(char));
	if (!tab)
		return (0);
	i = 0;
	while (s[i] && i < size)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

static int	ft_free_all(char **arrstr)
{
	int	i;

	i = 0;
	while (arrstr[i])
	{
		free(arrstr[i]);
		i++;
	}
	free(arrstr);
	return (0);
}

static int	ft_add_words(char **arrstr, const char *s, char c)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			size = 0;
			while (s[i] != c && s[i])
			{
				i++;
				size++;
			}
			arrstr[j] = ft_str_add_array(s + i - size, size, arrstr[j]);
			if (!arrstr[j])
				return (ft_free_all(arrstr));
			j++;
		}
	}
	return (1);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			words++;
		}
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char	**arrstr;

	if (!s || !s[0])
		return (0);
	arrstr = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arrstr)
		return (0);
	arrstr[ft_count_words(s, c)] = 0;
	if (!ft_add_words(arrstr, s, c))
		return (0);
	return (arrstr);
}

// int	main(void)
// {
// 	// char *string = "  qaa  qaa  ";
// 	char *string = "hello!";
// 	// char *string = "                  olol";
// 	char deli = ' ';
// 	int i = 0;
// 	char **res = ft_split(string, deli);
// 	while (res[i] != 0)
// 	{
// 		printf("%s \n", res[i]);
// 		i++;
// 	}
// 	return (1);
// }
