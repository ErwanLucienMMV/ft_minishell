/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_merge_quoted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:30:32 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/03 17:33:06 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	group_has_is_delimiter(t_parser *cur)
{
	t_parser	*tmp;

	tmp = cur;
	while (tmp && tmp->type != T_SPACE && tmp->type != PIPE)
	{
		if (tmp->type == IS_DELIMITER)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	strip_quotes_if_no_delimiter(t_parser *cur)
{
	t_parser	*tmp;

	if (group_has_is_delimiter(cur))
		return ;
	tmp = cur;
	while (tmp && tmp->type != T_SPACE)
	{
		if (is_expanded_type(tmp->type)
			&& (ft_strncmp(tmp->s, "\"\"", 3) == 0
				|| ft_strncmp(tmp->s, "\'\'", 3) == 0))
		{
			free(tmp->s);
			tmp->s = ft_strdup("");
		}
		tmp = tmp->next;
	}
}

char	*wrap_with_quote(char *s, char quote)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(s);
	new_str = malloc(len + 3);
	if (!new_str)
		return (NULL);
	new_str[0] = quote;
	ft_strlcpy(new_str + 1, s, len + 1);
	new_str[len + 1] = quote;
	new_str[len + 2] = '\0';
	return (new_str);
}

int	add_quotes_for_delimiter(t_parser *cur)
{
	t_parser	*tmp;
	char		*new_str;
	char		quote;

	if (!group_has_is_delimiter(cur))
		return (0);
	tmp = cur;
	while (tmp && tmp->type != T_SPACE)
	{
		if (tmp->type == WAS_DQUOTED || tmp->type == WAS_SQUOTED)
		{
			quote = '"';
			if (tmp->type == WAS_SQUOTED)
				quote = '\'';
			new_str = wrap_with_quote(tmp->s, quote);
			if (!new_str)
				return (1);
			free(tmp->s);
			tmp->s = new_str;
		}
		tmp = tmp->next;
	}
	return (0);
}
