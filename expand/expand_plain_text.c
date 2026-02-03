/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plain_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:11:25 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/03 13:59:56 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_plain_text(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (node->s[i] == '$' && ft_isalnum(node->s[i + 1]))
		{
			int start = i + 1;
			while (node->s[start] && ft_isalnum(node->s[start]))
				start++;
			char *key = ft_substr(node->s, i + 1, start - (i + 1));
			char *value = get_env_value_by_key(&envpath, key);
			free(key);
			if (value)
			{
				int k = 0;
				while (value[k])
					new_str[j++] = value[k++];
			}
			i = start;
		}
		else
			new_str[j++] = node->s[i++];
	}
	new_str[j] = '\0';
	free(node->s);
	node->s = new_str;
	return (0);
}
