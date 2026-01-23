/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:59:16 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:08:15 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*strjoined;

	strjoined = malloc((1 + ft_strlen(s1) + ft_strlen(s2)) * sizeof(char));
	if (!strjoined)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		strjoined[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strjoined[i + j] = s2[j];
		j++;
	}
	strjoined[i + j] = 0;
	return (strjoined);
}

// int	main(void)
// {
// 	char *s1 = "coucou";
// 	char *s2 = " a tous";
// 	printf("%s \n", ft_strjoin(s1, s2));
// 	return (1);
// }
