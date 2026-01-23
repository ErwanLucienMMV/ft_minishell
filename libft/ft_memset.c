/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:36:28 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:16:39 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)ptr;
	i = 0;
	while (i < count)
	{
		s[i] = value;
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	char *buffer1 = malloc(5 * sizeof(char));
// 	char *buffer2 = malloc(5 * sizeof(char));
// 	ft_memset(buffer1, 'B', 5);
// 	memset(buffer2, 'A', 5);
// 	printf("%s \n", buffer1);
// 	printf("%s \n", buffer2);
// }
