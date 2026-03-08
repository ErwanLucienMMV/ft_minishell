/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plain_text_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:00:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 00:53:30 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	contains_env_var(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$'
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

int	get_key_end(char *s, int start)
{
	int	end;

	end = start + 1;
	if (s[end] == '?')
		end++;
	else if (ft_isdigit(s[end]))
		end++;
	else
	{
		while (s[end] && (ft_isalnum(s[end]) || s[end] == '_'))
			end++;
	}
	return (end);
}

char	*get_value(char *key, t_envpath *envpath, int status)
{
	char	*status_str;

	if (key[0] == '?' && key[1] == '\0')
	{
		status_str = ft_itoa(status);
		return (status_str);
	}
	return (get_env_value_by_key(&envpath, key));
}

int	is_expandable(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int	reparse_and_replace(t_parser *node)
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
