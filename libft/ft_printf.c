/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:00:32 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 20:34:35 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		count;
	char	*s;
	int		i;
	va_list	param;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	s = (char *)str;
	va_start(param, str);
	while (s[i])
	{
		if (s[i] == '%')
			count += ft_print_with_param(fd, s[++i], param);
		else
			count += ft_putchar(fd, s[i]);
		i++;
	}
	va_end(param);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	char	*s;
	int		i;
	va_list	param;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	s = (char *)str;
	va_start(param, str);
	while (s[i])
	{
		if (s[i] == '%')
			count += ft_print_with_param(1, s[++i], param);
		else
			count += ft_putchar(1, s[i]);
		i++;
	}
	va_end(param);
	return (count);
}

// int main(void)
// {
// 	int j = printf(0);
// 	// printf("%d\n", j);
// 	int i = ft_printf(0);
// 	// printf("%d\n", i);
// 	return (1);
// }