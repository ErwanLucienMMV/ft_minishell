/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:01:32 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 20:44:33 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
	{
		i++;
	}
	return (i);
}

// int main(void)
// {
//     printf("ft_strlen('A') = %d\n", ft_strlen("Abcc"));
//     printf("strlen('a') = %lu \n", strlen("Abcc"));
//     return 1;
// }