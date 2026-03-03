/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:43:04 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/03 15:52:50 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static int	count_real_char(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	*search_and_replace(t_parser *node, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((count_real_char(node->s, c) + 1) * sizeof(char));
	while (node->s[i])
	{
		if (node->s[i] != c)
		{
			result[j] = node->s[i];
			j++;
		}
		i++;
	}
	result[j] = 0;
	free(node->s);
	node->s = result;
	return (result);
}
