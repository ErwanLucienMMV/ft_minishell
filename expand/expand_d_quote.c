/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 16:28:52 by abarthes         ###   ########.fr       */
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

static int	append_value(char **new_str, int *indice, char *value)
{
	int	k;

	k = 0;
	while (value && value[k])
		(*new_str)[indice[1]++] = value[k++];
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
	if (append_value(new_str, indice, value))
		return (free(key), 1);
	return (free(key), 0);
}

static int	build_dquote_string(
	t_parser *node,
	t_envpath *envpath,
	char *new_str,
	int len)
{
	int	ind[2];

	ind[0] = 1;
	ind[1] = 0;
	while (ind[0] < len - 1)
	{
		if (is_env_var(node, ind[0]))
		{
			if (handle_env_var(node, envpath, &new_str, ind))
				return (1);
			continue ;
		}
		new_str[ind[1]++] = node->s[ind[0]++];
	}
	new_str[ind[1]] = '\0';
	return (0);
}

int	expand_d_quote(t_parser **node, t_envpath *envpath)
{
	char	*new_str;
	int		len;
	int		final_size;

	len = ft_strlen((*node)->s);
	final_size = calculate_final_size(*node, envpath, len);
	new_str = malloc(sizeof(char) * final_size);
	if (!new_str)
		return (1);
	if (build_dquote_string(*node, envpath, new_str, len))
		return (free(new_str), 1);
	free((*node)->s);
	if (new_str[0] == '\0')
	{
		free(new_str);
		(*node)->s = ft_strdup("");
	}
	else
		(*node)->s = new_str;
	(*node)->type = WAS_EXPANDED;
	return (0);
}
