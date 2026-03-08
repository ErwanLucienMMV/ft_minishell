/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_empty_nodes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:30:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:06:02 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	is_redir_type(t_lexer type)
{
	if (type == DELIMITER || type == REDIR_OUTPUT
		|| type == REDIR_INPUT || type == REDIR_OUTPUT_APP || type == PIPE)
		return (1);
	return (0);
}

int	calc_group_len(t_parser *cur)
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
