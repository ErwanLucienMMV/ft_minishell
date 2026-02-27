/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:04:09 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/27 14:25:53 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	free_and_reset_node(t_parser *node, char *new_str)
{
	free(node->s);
	node->s = new_str;
}

int	remove_useless_space_nodes(t_program *program)
{
	t_parser	*cur;
	t_parser	*next;

	cur = *program->parsed;
	while (cur)
	{
		next = cur->next;
		if (cur->type == T_SPACE)
		{
			parser_clear_one(&cur, program);
		}
		cur = next;
	}
	return (0);
}

void	set_node_type(t_parser *node)
{
	if (node->type == REDIR_INPUT || node->type == REDIR_OUTPUT
		|| node->type == REDIR_OUTPUT_APP || node->type == PIPE
		|| node->type == DELIMITER || node->type == IS_DELIMITER)
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
