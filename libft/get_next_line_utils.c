/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:48:20 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 14:42:46 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*strjoined;

	if (!s1)
		strjoined = malloc((1 + ft_strlen(s2)) * sizeof(char));
	else
		strjoined = malloc((1 + ft_strlen(s1) + ft_strlen(s2)) * sizeof(char));
	if (!strjoined)
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		strjoined[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		strjoined[i + j] = s2[j];
		j++;
	}
	free(s1);
	strjoined[i + j] = 0;
	return (strjoined);
}

int	ft_get_newline(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	if (buffer[i] == 0)
		return (i - 1);
	return (0);
}
