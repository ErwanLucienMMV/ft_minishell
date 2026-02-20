/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 06:57:41 by emaigne          ###   ########.fr       */
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
	return (node->s[i] == '$'
		&& (ft_isalnum(node->s[i + 1]) || node->s[i + 1] == '_'));
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

void	set_node_type(t_parser *node)
{
	if (node->type == REDIR_INPUT || node->type == REDIR_OUTPUT
		|| node->type == REDIR_OUTPUT_APP || node->type == PIPE
		|| node->type == DELIMITER)
		return ;
	if (node->prev && (node->prev->type == REDIR_INPUT
			|| node->prev->type == REDIR_OUTPUT
			|| node->prev->type == REDIR_OUTPUT_APP))
		node->type = FILENAME;
	else if (node->prev && (node->prev->type == CMD
			|| node->prev->type == CMD_ARG))
		node->type = CMD_ARG;
	else
		node->type = CMD;
}

void	parser_clear_one(t_parser **node, t_program *program)
{
	t_parser	*next;
	t_parser	*prev;

	if (!(*node))
		return ;
	if (!(*node)->prev && (*node)->next)
		*(program->parsed) = (*node)->next;
	if (!(*node)->next && !(*node)->prev)
		*(program->parsed) = 0;
	next = (*node)->next;
	prev = (*node)->prev;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free((*node)->s);
	free((*node));
	(*node) = 0;
}

int	expand_d_quote(t_parser **node, t_envpath *envpath)
{
	char	*new_str;
	int		indice[2];
	int		len;

	len = ft_strlen((*node)->s);
	new_str = malloc(len * sizeof(char));
	if (!new_str)
		return (1);
	indice[0] = 1;
	indice[1] = 0;
	while (indice[0] < len - 1)
	{
		if (is_env_var((*node), indice[0]))
		{
			if (handle_env_var((*node), envpath, &new_str, indice))
				return (free(new_str), 1);
			continue ;
		}
		else
		{
			new_str[indice[1]++] = (*node)->s[indice[0]++];
		}
	}
	new_str[indice[1]] = '\0';
	free((*node)->s);
	if (new_str[0] == 0)
		(*node)->s = ft_strdup("");
	else
		(*node)->s = new_str;
	(*node)->type = WAS_EXPANDED;
	return (0);
}
