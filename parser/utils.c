/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:48:39 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/16 12:33:19 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*get_last_parser(t_parser *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_parser	*get_first_parser(t_parser *lst)
{
	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

void	parser_clear_one(t_parser **node)
{
	if (!(*node))
		return ;
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	free((*node)->s);
	free((*node));
	(*node) = 0;
}

int	new_parser(t_parser **head, t_parser *new_node)
{
	if (!new_node)
		return (0);
	parser_add_back(head, new_node);
	return (1);
}

t_parser	*get_prev_echo(t_parser *node)
{
	t_parser	*temp;

	temp = 0;
	if (!node)
		return (NULL);
	while (node)
	{
		if (node->type != CMD && node->type != CMD_ARG && node->type != ENVVAR && node->type != EXIT_STATUS && node->type != DQUOTE && node->type != SQUOTE)
			return (temp);
		if (node->type == CMD && ft_strncmp(node->s, "echo", 4) == 0 && ft_strlen(node->s) == 4)
			temp = node;
		node = node->prev;
	}
	return (temp);
}
