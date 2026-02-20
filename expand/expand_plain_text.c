/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plain_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:11:25 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:02:23 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	contains_env_var(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && ft_isalnum(s[i + 1]))
			return (1);
		i++;
	}
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

static int	build_plain_expansion(t_parser *node,
	t_envpath *envpath, char **new_str)
{
	int	indices[2];
	int	all_len;

	if (!contains_env_var(node->s))
		return (0);
	all_len = check_and_count_for_envvar(node, envpath);
	if (all_len < 0)
		return (1);
	*new_str = malloc(sizeof(char) * (all_len + 1));
	if (!*new_str)
		return (1);
	indices[0] = 0;
	indices[1] = 0;
	while (node->s[indices[0]])
	{
		if (node->s[indices[0]] == '$' && ft_isalnum(node->s[indices[0] + 1]))
		{
			if (handle_plain_env_var(node, envpath, *new_str, indices))
				return (free(*new_str), 1);
		}
		else
			(*new_str)[indices[1]++] = node->s[indices[0]++];
	}
	(*new_str)[indices[1]] = '\0';
	return (2);
}

static int	reparse_and_replace(t_parser *node)
{
	t_parser	*expanded;
	t_parser	*next;

	expanded = parsing(node->s);
	if (!expanded)
		return (1);
	next = node->next;
	replace_with_expansion(&node, expanded);
	attach_tail(node, next);
	mark_expanded_nodes(node, next);
	return (0);
}

int	expand_plain_text(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		status;

	status = build_plain_expansion(node, envpath, &new_str);
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

// int	expand_plain_text(t_parser *node, t_envpath *envpath)
// {
// 	char	*new_str;
// 	int		indices[2];
// 	int		all_len;	

// 	if (!contains_env_var(node->s))
// 		return (0);
// 	all_len = check_and_count_for_envvar(node, envpath);
// 	if (all_len == -1)
// 		return (1);
// 	new_str = malloc((all_len + 1) * sizeof(char));
// 	if (!new_str)
// 		return (1);
// 	ft_memset(indices, 0, 2 * sizeof(int));
// 	while (indices[0] < (int)ft_strlen(node->s))
// 	{
// 		if (node->s[indices[0]] == '$' && ft_isalnum(node->s[indices[0] + 1]))
// 		{
// 			if (handle_plain_env_var(node, envpath, new_str, indices))
// 				return (free(new_str), 1);
// 		}
// 		else
// 			new_str[indices[1]++] = node->s[indices[0]++];
// 	}
// 	new_str[indices[1]] = '\0';
// 	free_and_reset_node(node, new_str);
// 	node->type = WAS_EXPANDED;
// 	t_parser	*expanded_one = parsing(node->s);
// 	t_parser	*expanded_next;
// 	t_parser	*next;
// 	t_parser	*prev;
// 	if (!expanded_one)
// 		return (1);
// 	expanded_next = expanded_one->next;
// 	prev = node->prev;
// 	next = node->next;
// 	free(node->s);
// 	node->type = expanded_one->type;
// 	node->s = expanded_one->s;
// 	node->prev = prev;
// 	node->next = expanded_next;
// 	if (expanded_next)
// 		expanded_next->prev = node;
// 	if (prev)
// 		prev->next = node;
// 	if (next)
// 	{
// 		t_parser	*tail = get_last_parser(node);
// 		next->prev = tail;
// 		tail->next = next;
// 	}
// 	t_parser	*cur;
// 	t_parser	*stop;

// 	cur = node;
// 	stop = next;
// 	while (cur && cur != stop)
// 	{
// 		if (cur->type != T_SPACE)
// 			cur->type = WAS_EXPANDED;
// 		cur = cur->next;
// 	}
// 	free(expanded_one);
// 	return (0);
// }