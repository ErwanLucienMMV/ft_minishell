/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:21:25 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:08:56 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*output;

	i = 0;
	output = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!output)
		return (0);
	while (s[i])
	{
		output[i] = f(i, s[i]);
		i++;
	}
	output[i] = 0;
	return (output);
}

// int main(void)
// {
// 	printf("%s \n", ft_strmapi("coucou", ft_toup));
// }
