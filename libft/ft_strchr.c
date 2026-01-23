/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:36:31 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:19:26 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	while (*str && *str != c % 256)
		str++;
	if (*str == c % 256)
		return ((char *)str);
	return (0);
}

// int	main(void)
// {
// 	char *src = "there is so ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
// 	printf("strchr : %s \n", strchr("teste", 'e'));
// 	printf("ft_strchr : %s \n", ft_strchr("teste", 'e'));
// 	return (1);
// }