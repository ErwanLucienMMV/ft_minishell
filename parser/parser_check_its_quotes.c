/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_its_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:19:24 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/06 12:27:10 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	its_d_quote(t_parser **head, char *s, int *i)
{
	int		x;

	x = 1;
	while (s[x] && s[x] != '"')
		x++;
	x++;
	if (s[x - 1] != '"')
		return (0);
	if (get_prev_non_space(get_last_parser(*head))
		&& get_prev_non_space(get_last_parser(*head))->type == DELIMITER)
	{
		if (new_parser(head, parser_node_new(IS_DELIMITER,
					(s), x)) == 0)
			return (0);
		*i += x;
		return (1);
	}
	if (new_parser(head, parser_node_new(DQUOTE, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	its_s_quote(t_parser **head, char *s, int *i)
{
	int		x;

	x = 1;
	while (s[x] && s[x] != '\'')
		x++;
	x++;
	if (s[x - 1] != '\'')
		return (0);
	if (get_prev_non_space(get_last_parser(*head))
		&& get_prev_non_space(get_last_parser(*head))->type == DELIMITER)
	{
		if (new_parser(head, parser_node_new(IS_DELIMITER,
					(s), x)) == 0)
			return (0);
		*i += x;
		return (1);
	}
	if (new_parser(head, parser_node_new(SQUOTE, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

// int	its_d_quote(t_parser **head, char *s, int *i)
// {
// 	int		x;

// 	x = 1;
// 	while (s[x] && s[x] != '"')
// 		x++;
// 	x++;
// 	if (s[x - 1] != '"')
// 		return (0);
// 	// NEW: Check if this is for a DELIMITER and the content is empty
// 	if (get_prev_non_space(get_last_parser(*head))
// 		&& get_prev_non_space(get_last_parser(*head))->type == DELIMITER)
// 	{
// 		// Check if delimiter content is empty (x == 2 means just "" with nothing inside)
// 		if (x == 2)
// 		{
// 			ft_putstr_fd("minishell: syntax error: empty delimiter\n", 2);
// 			return (0);
// 		}
// 		if (new_parser(head, parser_node_new(IS_DELIMITER,
// 					(s), x)) == 0)
// 			return (0);
// 		*i += x;
// 		return (1);
// 	}
// 	if (new_parser(head, parser_node_new(DQUOTE, (s), x)) == 0)
// 		return (0);
// 	*i += x;
// 	return (1);
// }

// int	its_s_quote(t_parser **head, char *s, int *i)
// {
// 	int		x;

// 	x = 1;
// 	while (s[x] && s[x] != '\'')
// 		x++;
// 	x++;
// 	if (s[x - 1] != '\'')
// 		return (0);
// 	// NEW: Check if this is for a DELIMITER and the content is empty
// 	if (get_prev_non_space(get_last_parser(*head))
// 		&& get_prev_non_space(get_last_parser(*head))->type == DELIMITER)
// 	{
// 		// Check if delimiter content is empty (x == 2 means just '' with nothing inside)
// 		if (x == 2)
// 		{
// 			ft_putstr_fd("minishell: syntax error: empty delimiter\n", 2);
// 			return (0);
// 		}
// 		if (new_parser(head, parser_node_new(IS_DELIMITER,
// 					(s), x)) == 0)
// 			return (0);
// 		*i += x;
// 		return (1);
// 	}
// 	if (new_parser(head, parser_node_new(SQUOTE, (s), x)) == 0)
// 		return (0);
// 	*i += x;
// 	return (1);
// }
