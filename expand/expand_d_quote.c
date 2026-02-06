/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/06 19:23:52 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	get_env_key(t_parser *node, int *indice, char **key)
{
	int		end;
	int		start;
	int		len;

	start = indice[0] + 1;
	end = start;
	while (node->s[end] && ft_isalnum(node->s[end]))
		end++;
	len = end - start;
	*key = ft_substr(node->s, start, len);
	if (!*key)
		return (1);
	indice[0] = end;
	return (0);
}

static int	is_env_var(t_parser *node, int i)
{
	return (node->s[i] == '$' && ft_isalnum(node->s[i + 1]));
}

static int	append_value(char **new_str, int *indice, char *value)
{
	char	*temp;
	size_t	value_len;

	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	temp = malloc(indice[1] + value_len + 1);
	if (!temp)
		return (1);
	ft_memcpy(temp, *new_str, indice[1]);
	temp[indice[1]] = '\0';
	free(*new_str);
	*new_str = temp;
	while (value && value[indice[2]])
		(*new_str)[indice[1]++] = value[indice[2]++];
	(*new_str)[indice[1]] = '\0';
	return (0);
}

static int	handle_env_var(t_parser *node, t_envpath *envpath,
	char **new_str, int *indice)
{
	char	*key;
	char	*value;

	if (get_env_key(node, indice, &key))
		return (1);
	value = get_env_value_by_key(&envpath, key);
	indice[2] = 0;
	if (append_value(new_str, indice, value))
		return (free(key), 1);
	return (free(key), 0);
}

static void	set_node_type(t_parser *node)
{
	if (node->prev && node->prev->type == CMD)
		node->type = CMD_ARG;
	else
		node->type = CMD;
}

static int	init_expand(t_parser *node, char **new_str, int *indice, int *len)
{
	*len = ft_strlen(node->s);
	*new_str = malloc((*len - 1) * sizeof(char));
	if (!*new_str)
		return (1);
	indice[0] = 1;
	indice[1] = 0;
	return (0);
}

int	expand_d_quote(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		indice[3];
	int		len;
	if (init_expand(node, &new_str, indice, &len))
		return (1);
	while (indice[0] < len - 1)
	{
		if (is_env_var(node, indice[0]))
		{
			if (handle_env_var(node, envpath, &new_str, indice))
				return (free(new_str), 1);
			continue;
		}
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
