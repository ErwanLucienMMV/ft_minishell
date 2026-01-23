/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:44:21 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 20:31:21 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_with_param(int fd, int c, va_list params)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar(fd, va_arg(params, int));
	else if (c == 's')
		count = ft_putstr(fd, va_arg(params, char *));
	else if (c == 'p')
		count = ft_putpointer(fd, va_arg(params, unsigned long long),
				"0123456789abcdef");
	else if (c == 'd' || c == 'i')
		count = ft_putnbr_base(fd, va_arg(params, int), "0123456789");
	else if (c == 'u')
		count = ft_putnbr_base_unsigned(fd, va_arg(params, unsigned int),
				"0123456789");
	else if (c == 'x')
		count = ft_putnbr_base_unsigned(fd, va_arg(params, unsigned int),
				"0123456789abcdef");
	else if (c == 'X')
		count = ft_putnbr_base_unsigned(fd, va_arg(params, unsigned int),
				"0123456789ABCDEF");
	else if (c == '%')
		count = ft_putchar(fd, '%');
	return (count);
}
