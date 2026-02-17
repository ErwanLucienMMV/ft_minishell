/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:48:39 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/17 16:19:05 by abarthes         ###   ########.fr       */
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
	node = node->prev;
	while (node)
	{
		if (node->type == PIPE)
			return (temp);
		if ((node->type == CMD || node->type == CMD_ARG) && ft_strncmp(node->s, "echo", 4) == 0 && ft_strlen(node->s) == 4)
			return (node);
		node = node->prev;
	}
	return (temp);
}
