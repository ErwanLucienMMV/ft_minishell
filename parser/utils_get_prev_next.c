/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_prev_next.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:27:48 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 17:29:05 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*get_prev_echo(t_parser *node)
{
	t_parser	*temp;

	temp = 0;
	if (!node)
		return (NULL);
	node = node->prev;
	while (node)
	{
		if (node->type == PIPE)
			return (temp);
		if ((node->type == CMD || node->type == CMD_ARG)
			&& ft_strncmp(node->s, "echo", 4) == 0 && ft_strlen(node->s) == 4)
			return (node);
		node = node->prev;
	}
	return (temp);
}

t_parser	*get_next_non_space(t_parser *token)
{
	if (!token)
		return (NULL);
	while (token && token->type == T_SPACE && token->next)
		token = token->next;
	return (token);
}

t_parser	*get_prev_non_space(t_parser *token)
{
	if (!token)
		return (NULL);
	while (token && token->type == T_SPACE && token->prev)
		token = token->prev;
	return (token);
}
