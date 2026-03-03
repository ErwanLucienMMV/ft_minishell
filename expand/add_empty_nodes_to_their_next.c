/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_empty_nodes_to_their_next.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:14:17 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/03 16:11:53 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	calc_group_len(t_parser *cur)
{
	t_parser	*tmp;
	int			count;

	count = ft_strlen(cur->s);
	tmp = cur->next;
	while (tmp && tmp->type != T_SPACE)
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
	while (tmp && tmp->type != T_SPACE)
	{
		if (tmp->type == WAS_EXPANDED)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	group_has_is_delimiter(t_parser *cur)
{
	t_parser	*tmp;

	tmp = cur;
	while (tmp && tmp->type != T_SPACE)
	{
		if (tmp->type == IS_DELIMITER)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	strip_quotes_if_no_delimiter(t_parser *cur)
{
	t_parser	*tmp;

	if (group_has_is_delimiter(cur))
		return ;
	tmp = cur;
	while (tmp && tmp->type != T_SPACE)
	{
		if (tmp->type == WAS_EXPANDED
			&& (ft_strncmp(tmp->s, "\"\"", 3) == 0
				|| ft_strncmp(tmp->s, "\'\'", 3) == 0))
		{
			free(tmp->s);
			tmp->s = ft_strdup("");
		}
		tmp = tmp->next;
	}
}

int	add_empty_nodes_to_their_next(t_program *program)
{
	t_parser	*cur;
	int			len;

	print_debug(program);
	cur = *(program->parsed);
	while (cur)
	{
		if (cur->type != T_SPACE
			&& (cur->type == WAS_EXPANDED || has_was_expanded_next(cur)))
		{
			strip_quotes_if_no_delimiter(cur);
			len = calc_group_len(cur);
			if (merge_nodes(program, cur, len))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
