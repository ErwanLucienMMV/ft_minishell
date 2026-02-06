/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plain_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:11:25 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/03 22:48:57 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	copy_env_value(char *new_str, int *j, char *value)
{
	int	k;

	k = 0;
	while (value && value[k])
		new_str[(*j)++] = value[k++];
	return (0);
}

int	handle_plain_env_var(t_parser *node, t_envpath *envpath,
	char *new_str, int *indices)
{
	char	*key;
	char	*value;
	int		end;

	end = indices[0] + 1;
	while (node->s[end] && ft_isalnum(node->s[end]))
		end++;
	key = ft_substr(node->s, indices[0] + 1, end - (indices[0] + 1));
	if (!key)
		return (1);
	value = get_env_value_by_key(&envpath, key);
	copy_env_value(new_str, &indices[1], value);
	indices[0] = end;
	return (free(key), 0);
}

int	expand_plain_text(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		indices[2];
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (1);
	indices[0] = 0;
	indices[1] = 0;
	while (indices[0] < len)
	{
		if (node->s[indices[0]] == '$' && ft_isalnum(node->s[indices[0] + 1]))
		{
			if (handle_plain_env_var(node, envpath, new_str, indices))
				return (free(new_str), 1);
		}
		else
			new_str[indices[1]++] = node->s[indices[0]++];
	}
	new_str[indices[1]] = '\0';
	free(node->s);
	node->s = new_str;
	return (0);
}

// int	expand_plain_text(t_parser *node, t_envpath *envpath)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;
// 	int		len;

// 	len = ft_strlen(node->s);
// 	new_str = malloc((len + 1) * sizeof(char));
// 	if (!new_str)
// 		return (1);
// 	i = 0;
// 	j = 0;
// 	while (i < len)
// 	{
// 		if (node->s[i] == '$' && ft_isalnum(node->s[i + 1]))
// 		{
// 			int start = i + 1;
// 			while (node->s[start] && ft_isalnum(node->s[start]))
// 				start++;
// 			char *key = ft_substr(node->s, i + 1, start - (i + 1));
// 			char *value = get_env_value_by_key(&envpath, key);
// 			free(key);
// 			if (value)
// 			{
// 				int k = 0;
// 				while (value[k])
// 					new_str[j++] = value[k++];
// 			}
// 			i = start;
// 		}
// 		else
// 			new_str[j++] = node->s[i++];
// 	}
// 	new_str[j] = '\0';
// 	free(node->s);
// 	node->s = new_str;
// 	return (0);
// }
