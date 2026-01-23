/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:33:19 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/14 12:37:49 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char *buffer1 = malloc(5 * sizeof(char));
// 	char *buffer2 = malloc(5 * sizeof(char));
// 	ft_bzero(buffer1, 5);
// 	bzero(buffer2, 5);
// 	printf("ft_bzero : %s \n", buffer1);
// 	printf("bzero : %s \n", buffer2);
// 	printf("%d", 0);
// }