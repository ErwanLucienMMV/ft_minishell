/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:22:51 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/03 18:14:47 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long	ft_strtol(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign += (str[i++] == '-');
	while (str[i] && ft_isdigit(str[i]))
	{
		if (result > LLONG_MAX / 10)
			return (-256);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign)
		return (result * -1);
	else
		return (result);
}
