/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/03 13:59:50 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_d_quote(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;
	char	*value;
	char	*key;
	int 	k;
	int 	start;

	len = ft_strlen(node->s);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (1);
	i = 1;
	j = 0;
	while (i < len - 1)
	{
		if (node->s[i] == '$' && ft_isalnum(node->s[i + 1]))
		{
			start = i + 1;
			while (node->s[start] && ft_isalnum(node->s[start]))
				start++;
			key = ft_substr(node->s, i + 1, start - (i + 1));
			value = get_env_value_by_key(&envpath, key);
			char *temp = malloc((ft_strlen(new_str) + ft_strlen(value)) * sizeof(char));
			if (!temp)
			{
				free(key);
				free(value);
				//Handle the free of the program from here
				return (1);
			}
			ft_strlcpy(temp, new_str, j + 1);
			free(new_str);
			new_str = temp;
			free(key);
			if (value)
			{
				k = 0;
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
	if (j == 0)
		parser_clear_one(node);
	if (node->prev && node->prev->type == CMD)
		node->type = CMD_ARG;
	else
		node->type = CMD;
	return (0);
}
