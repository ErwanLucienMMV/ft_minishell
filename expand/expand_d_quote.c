/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/08 01:08:58 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	get_env_key(t_parser *node, int *indice, char **key)
{
	int		end;
	int		start;
	int		len;

	start = indice[0] + 1;
	if (node->s[start] == '?')
	{
		*key = ft_strdup("?");
		if (!*key)
			return (1);
		indice[0] = start + 1;
		return (0);
	}
	end = start;
	while (node->s[end] && (ft_isalnum(node->s[end]) || node->s[end] == '_'))
		end++;
	len = end - start;
	*key = ft_substr(node->s, start, len);
	if (!*key)
		return (1);
	indice[0] = end;
	return (0);
}

static int	handle_env_var(t_dquote_data *data)
{
	char	*key;
	char	*value;
	char	*status_str;

	if (get_env_key(data->node, data->indice, &key))
		return (1);
	status_str = NULL;
	if (key[0] == '?' && key[1] == '\0')
	{
		status_str = ft_itoa(data->program->last_exit_status);
		if (!status_str)
			return (free(key), 1);
		value = status_str;
	}
	else
		value = get_env_value_by_key(&data->envpath, key);
	if (append_value(&data->new_str, data->indice, value))
		return (free(status_str), free(key), 1);
	return (free(status_str), free(key), 0);
}

static int	build_dquote_string(t_dquote_data *data, int len)
{
	data->indice[0] = 1;
	data->indice[1] = 0;
	while (data->indice[0] < len - 1)
	{
		if (is_env_var(data->node, data->indice[0]))
		{
			if (handle_env_var(data))
				return (1);
			continue ;
		}
		data->new_str[data->indice[1]++] = data->node->s[data->indice[0]++];
	}
	data->new_str[data->indice[1]] = '\0';
	return (0);
}

static void	finalize_dquote_result(t_parser **node, char *new_str)
{
	free((*node)->s);
	if (new_str[0] == '\0')
	{
		free(new_str);
		(*node)->s = ft_strdup("\"\"");
	}
	else
		(*node)->s = new_str;
	(*node)->type = WAS_DQUOTED;
}

int	expand_d_quote(t_parser **node, t_envpath *envpath, t_program *program)
{
	t_dquote_data	data;
	char			*new_str;
	int				len;
	int				final_size;
	int				indice[2];

	len = ft_strlen((*node)->s);
	final_size = calculate_final_size(*node, envpath, len,
			program->last_exit_status);
	if (final_size < 0)
		return (1);
	new_str = malloc(sizeof(char) * final_size);
	if (!new_str)
		return (1);
	indice[0] = 0;
	indice[1] = 0;
	data.node = *node;
	data.envpath = envpath;
	data.new_str = new_str;
	data.indice = indice;
	data.program = program;
	if (build_dquote_string(&data, len))
		return (free(new_str), 1);
	finalize_dquote_result(node, new_str);
	return (0);
}
