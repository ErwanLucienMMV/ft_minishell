/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:17:21 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/09 16:17:24 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_countdec(int nbr)
{
	int		i;
	long	n;

	n = nbr;
	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i + 1);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		i;
	long	n;

	n = nbr;
	if (n == 0)
		return (ft_strdup("0"));
	i = ft_countdec(n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[i--] = 0;
	while (n != 0)
	{
		str[i--] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

// int main(void)
// {
// 	printf("%s \n", ft_itoa(-2147483648));
// 	return (1);
// }
