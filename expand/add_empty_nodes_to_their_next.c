/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_empty_nodes_to_their_next.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:14:17 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/07 20:41:51 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	is_redir_type(t_lexer type)
{
	if (type == DELIMITER || type == REDIR_OUTPUT
		|| type == REDIR_INPUT || type == REDIR_OUTPUT_APP || type == PIPE)
		return (1);
	return (0);
}

static int	calc_group_len(t_parser *cur)
{
	t_parser	*tmp;
	int			count;

	count = ft_strlen(cur->s);
	tmp = cur->next;
	while (tmp && tmp->type != T_SPACE && !is_redir_type(tmp->type))
	{
		count += ft_strlen(tmp->s);
		tmp = tmp->next;
	}
	return (count);
}

static int	has_was_expanded_next(t_parser *cur)
{
	t_parser	*tmp;

	tmp = cur->next;
	while (tmp && tmp->type != T_SPACE && !is_redir_type(tmp->type))
	{
		if (is_expanded_type(tmp->type))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	should_merge_group(t_parser *cur)
{
	if (is_redir_type(cur->type))
		return (0);
	if (is_expanded_type(cur->type))
		return (1);
	if (has_was_expanded_next(cur))
		return (1);
	if (cur->type == IS_DELIMITER && cur->next
		&& cur->next->type != T_SPACE && !is_redir_type(cur->next->type))
		return (1);
	return (0);
}

int	add_empty_nodes_to_their_next(t_program *program)
{
	t_parser	*cur;
	t_parser	*next;
	int			len;

	print_debug(program);
	cur = *(program->parsed);
	while (cur)
	{
		next = cur->next;
		if (cur->type == CMD && ft_strncmp(cur->s, "$", 1) == 0 
			&& next && next->type != T_SPACE 
			&& (is_expanded_type(next->type) || next->type == WAS_SQUOTED || next->type == WAS_DQUOTED))
		{
			parser_clear_one(&cur, program);
			cur = next;
			continue;
		}
		if (cur->type != T_SPACE && should_merge_group(cur))
		{
			if (add_quotes_for_delimiter(cur))
				return (1);
			strip_quotes_if_no_delimiter(cur);
			len = calc_group_len(cur);
			if (merge_nodes(program, cur, len))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
