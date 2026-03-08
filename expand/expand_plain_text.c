/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plain_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:11:25 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/08 00:53:30 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	handle_plain_env_var(t_expand_data *data)
{
	char	*key;
	char	*value;
	int		end;
	int		is_status;

	end = get_key_end(data->node->s, data->indices[0]);
	key = ft_substr(data->node->s, data->indices[0] + 1,
			end - (data->indices[0] + 1));
	if (!key)
		return (1);
	value = get_value(key, data->envpath, data->status);
	is_status = (key[0] == '?' && key[1] == '\0');
	if (!value && is_status)
		return (free(key), 1);
	copy_env_value(data->new_str, &data->indices[1], value);
	if (is_status)
		free(value);
	data->indices[0] = end;
	return (free(key), 0);
}

static int	process_char(t_expand_data *data)
{
	if (data->node->s[data->indices[0]] == '$'
		&& is_expandable(data->node->s[data->indices[0] + 1]))
	{
		if (handle_plain_env_var(data))
			return (1);
	}
	else
		data->new_str[data->indices[1]++]
			= data->node->s[data->indices[0]++];
	return (0);
}

static int	build_plain_expansion(t_parser *node,
	t_envpath *envpath, char **new_str, int status)
{
	t_expand_data	data;
	int				all_len;

	if (!contains_env_var(node->s))
		return (0);
	all_len = check_and_count_for_envvar(node, envpath, status);
	if (all_len < 0)
		return (1);
	*new_str = malloc(sizeof(char) * (all_len + 1));
	if (!*new_str)
		return (1);
	data = (t_expand_data){node, envpath, *new_str, (int [2]){0, 0}, status};
	while (data.node->s[data.indices[0]])
	{
		if (process_char(&data))
			return (free(*new_str), 1);
	}
	data.new_str[data.indices[1]] = '\0';
	return (2);
}

int	expand_plain_text(t_parser *node, t_envpath *envpath, t_program *program)
{
	char	*new_str;
	int		status;

	status = build_plain_expansion(node, envpath,
			&new_str, program->last_exit_status);
	if (status == 0)
		return (0);
	if (status == 1)
		return (1);
	free(node->s);
	node->s = new_str;
	node->type = WAS_EXPANDED;
	if (reparse_and_replace(node))
		return (1);
	return (0);
}
