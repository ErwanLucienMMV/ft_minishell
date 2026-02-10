/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:43:30 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/10 12:36:49 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Search for a character in a string and return its pointer
char	*ft_strrchr(const char *str, int schar)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && str[i] != schar % 256)
		i--;
	if (str[i] == schar % 256)
		return ((char *)str + i);
	return (0);
}

// int	main(void)
// {
// 	char *str = "";
// 	int schar = '\0';
// 	printf("%s \n", ft_strrchr(str, schar));
// 	return (1);
// }
