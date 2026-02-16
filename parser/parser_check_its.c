/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_its.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:24:30 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/13 15:25:14 by abarthes         ###   ########.fr       */
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
	if (get_last_parser(*head) && get_last_parser(*head)->type == DELIMITER)
	{
		if (new_parser(head, parser_node_new(IS_DELIMITER,
					(s + 1), x - 2)) == 0)
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
	if (get_last_parser(*head) && get_last_parser(*head)->type == DELIMITER)
	{
		if (new_parser(head, parser_node_new(IS_DELIMITER,
					(s + 1), x - 2)) == 0)
			return (0);
		*i += x;
		return (1);
	}
	if (new_parser(head, parser_node_new(SQUOTE, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	its_exit_status(t_parser **head, char *s, int *i)
{
	if (new_parser(head, parser_node_new(EXIT_STATUS, (s), 2)) == 0)
		return (0);
	*i += 2;
	return (1);
}

int	its_pipe(t_parser **head, char *s, int *i)
{
	if (new_parser(head, parser_node_new(PIPE, (s), 1)) == 0)
		return (0);
	*i += 1;
	return (1);
}

int	its_command(t_parser **head, char *s, int *i)
{
	int			x;
	t_parser	*new;

	x = 0;
	new = NULL;
	while (s[x] && s[x] != ' ' && s[x] != '\t' && s[x] != '|' && s[x] != '<'
		&& s[x] != '>' && s[x] != '\'' && s[x] != '"')
		x++;
	if (get_last_parser(*head) && !(get_last_parser(*head)->type == REDIR_OUTPUT
			|| get_last_parser(*head)->type == REDIR_OUTPUT_APP
			|| get_last_parser(*head)->type == REDIR_INPUT
			|| get_last_parser(*head)->type == DELIMITER
			|| get_last_parser(*head)->type == PIPE))
		new = parser_node_new(CMD_ARG, (s), x);
	if (get_last_parser(*head) && (get_last_parser(*head)->type == REDIR_OUTPUT
			|| get_last_parser(*head)->type == REDIR_OUTPUT_APP
			|| get_last_parser(*head)->type == REDIR_INPUT))
		new = parser_node_new(FILENAME, (s), x);
	if (get_last_parser(*head) && get_last_parser(*head)->type == DELIMITER)
		new = parser_node_new(IS_DELIMITER, (s), x);
	if (new == NULL)
		new = parser_node_new(CMD, (s), x);
	if (new == 0)
		return (0);
	new_parser(head, new);
	*i += x;
	return (1);
}
