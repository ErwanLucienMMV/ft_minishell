/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_empty_nodes_to_their_next.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:14:17 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 15:44:02 by abarthes         ###   ########.fr       */
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

static int	merge_nodes(t_program *program, t_parser *cur, int len)
{
	t_parser	*tmp;
	t_parser	*to_remove;
	char		*str;

	tmp = cur->next;
	if (!tmp || tmp->type == T_SPACE)
		return (0);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (1);
	str[0] = '\0';
	ft_strlcat(str, cur->s, len + 1);
	while (tmp && tmp->type != T_SPACE)
	{
		to_remove = tmp;
		ft_strlcat(str, tmp->s, len + 1);
		tmp = tmp->next;
		parser_clear_one(&to_remove, program);
	}
	free(cur->s);
	cur->s = str;
	cur->next = tmp;
	return (0);
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

int	add_empty_nodes_to_their_next(t_program *program)
{
	t_parser	*cur;
	int			len;

	print_debug(program);
	cur = *(program->parsed);
	while (cur)
	{
		if (cur->type != T_SPACE && has_was_expanded_next(cur))
		{
			len = calc_group_len(cur);
			if (merge_nodes(program, cur, len))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

// int	add_empty_nodes_to_their_next(t_program *program)
// {
// 	t_parser	*cur;
// 	t_parser	*to_remove;
// 	t_parser	*expanded;
// 	char	*str;
// 	int		count;
// 	int		buf_size;

// 	print_debug(program);
// 	cur = *(program->parsed);
// 	while (cur)
// 	{
// 		if (cur->type == T_SPACE)
// 		{
// 			cur = cur->next;
// 			continue ;
// 		}
// 		expanded = cur->next;
// 		count = ft_strlen(cur->s);
// 		while (expanded && expanded->type != T_SPACE)
// 		{
// 			count += ft_strlen(expanded->s);
// 			expanded = expanded->next;
// 		}
// 		if (!expanded || expanded->type == T_SPACE)
// 		{
// 			expanded = cur->next;
// 			if (expanded && expanded->type != T_SPACE)
// 			{
// 				buf_size = count + 1;
// 				str = malloc(buf_size * sizeof(char));
// 				if (!str)
// 					return (1);
// 				str[0] = '\0';
// 				ft_strlcat(str, cur->s, buf_size);
// 				while (expanded && expanded->type != T_SPACE)
// 				{
// 					to_remove = expanded;
// 					ft_strlcat(str, expanded->s, buf_size);
// 					expanded = expanded->next;
// 					parser_clear_one(&to_remove, program);
// 				}
// 				free(cur->s);
// 				cur->s = str;
// 				cur->next = expanded;
// 			}
// 		}
// 		cur = cur->next;
// 	}
// 	return (0);
// }