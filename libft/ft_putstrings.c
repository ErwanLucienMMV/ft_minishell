/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:04:01 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 20:32:43 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr(fd, "(null)"));
	while (str[i])
		ft_putchar(fd, str[i++]);
	return (i);
}

int	ft_putnbr_base(int fd, int nbr, char *base)
{
	long	n;
	int		count;

	n = nbr;
	count = 0;
	if (n < 0)
	{
		n *= -1;
		ft_putchar(fd, '-');
		count++;
	}
	if (n >= (int)ft_strlen(base))
	{
		count += ft_putnbr_base(fd, n / ft_strlen(base), base);
	}
	count += ft_putchar(fd, base[n % ft_strlen(base)]);
	return (count);
}

int	ft_putnbr_base_unsigned(int fd, unsigned int nbr, char *base)
{
	long	n;
	int		count;

	n = nbr;
	count = 0;
	if (n < 0)
	{
		n *= -1;
		ft_putchar(fd, '-');
		count++;
	}
	if (n >= (int)ft_strlen(base))
	{
		count += ft_putnbr_base(fd, n / ft_strlen(base), base);
	}
	count += ft_putchar(fd, base[n % ft_strlen(base)]);
	return (count);
}

int	ft_putpointer(int fd, unsigned long long ptr, char *base)
{
	int		count;

	count = 0;
	if (!ptr)
		return (ft_putstr(fd, "(nil)"));
	if (ptr >= 16)
	{
		count += ft_putpointer(fd, ptr / 16, base);
	}
	else
	{
		count += ft_putstr(fd, "0x");
	}
	count += ft_putchar(fd, base[ptr % 16]);
	return (count);
}
