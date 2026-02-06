/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/03 22:44:31 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int static	handle_env_var(t_parser *node, t_envpath *envpath,
	char **new_str, int *indice)
{
	char	*value;
	char	*key;
	char	*temp;
	int		end;

	end = indice[0] + 1;
	while (node->s[end] && ft_isalnum(node->s[end]))
		end++;
	key = ft_substr(node->s, indice[0] + 1, end - (indice[0] + 1));
	if (!key)
		return (1);
	value = get_env_value_by_key(&envpath, key);
	temp = malloc(ft_strlen(*new_str) + ft_strlen(value) + 1);
	if (!temp)
		return (free(key), 1);
	ft_strlcpy(temp, *new_str, indice[1] + 1);
	free(*new_str);
	*new_str = temp;
	indice[2] = 0;
	while (value && value[indice[2]])
		(*new_str)[indice[1]++] = value[indice[2]++];
	indice[0] = end;
	return (free(key), 0);
}

void static	set_node_type(t_parser *node)
{
	if (node->prev && node->prev->type == CMD)
		node->type = CMD_ARG;
	else
		node->type = CMD;
}

int	expand_d_quote(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		indice[3];
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (1);
	indice[0] = 1;
	indice[1] = 0;
	while (indice[0] < len - 1)
	{
		if (node->s[indice[0]] == '$' && ft_isalnum(node->s[indice[0] + 1])
			&& (handle_env_var(node, envpath, &new_str, indice)))
			return (free(new_str), 1);
		if (!(node->s[indice[0]] == '$' && ft_isalnum(node->s[indice[0] + 1])))
			new_str[indice[1]++] = node->s[indice[0]++];
	}
	new_str[indice[1]] = '\0';
	free(node->s);
	node->s = new_str;
	if (indice[1] == 0)
		return (parser_clear_one(node), 0);
	set_node_type(node);
	return (0);
}
