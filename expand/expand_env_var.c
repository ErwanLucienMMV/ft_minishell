/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:28:43 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/27 14:41:45 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	replace_with_expansion(
	t_parser **node,
	t_parser *expanded_one)
{
	t_parser	*prev;
	t_parser	*expanded_next;

	prev = (*node)->prev;
	expanded_next = expanded_one->next;
	free((*node)->s);
	(*node)->type = expanded_one->type;
	(*node)->s = expanded_one->s;
	(*node)->prev = prev;
	(*node)->next = expanded_next;
	if (expanded_next)
		expanded_next->prev = *node;
	if (prev)
		prev->next = *node;
	free(expanded_one);
	return (0);
}

void	attach_tail(t_parser *node, t_parser *next)
{
	t_parser	*tail;

	if (!next)
		return ;
	tail = get_last_parser(node);
	next->prev = tail;
	tail->next = next;
}

void	mark_expanded_nodes(t_parser *start, t_parser *stop)
{
	t_parser	*cur;

	cur = start;
	while (cur && cur != stop)
	{
		if (cur->type != T_SPACE)
			cur->type = WAS_EXPANDED;
		cur = cur->next;
	}
}

int	expand_env_var(t_parser **node, t_envpath *envpath, t_program *program)
{
	char		*value;
	t_parser	*expanded;
	t_parser	*next;

	if (ft_strlen((*node)->s) == 0)
		return (set_node_type(*node), 0);
	value = get_env_value_by_key(&envpath, (*node)->s);
	if (!value)
		return (parser_clear_one(node, program), 0);
	expanded = parsing(value);
	if (!expanded)
		return (1);
	next = (*node)->next;
	replace_with_expansion(node, expanded);
	attach_tail(*node, next);
	mark_expanded_nodes(*node, next);
	return (0);
}
