/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:42:51 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/10 13:42:52 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int nbr, int fd)
{
	char	result;
	long	n;

	n = nbr;
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n == 2147483648)
	{
		write(fd, "2147483648", 10);
		return ;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	result = (n % 10) + '0';
	write(fd, &result, 1);
}

// int main(void)
// {
// 	ft_putnbr_fd(8, 1);
// }
