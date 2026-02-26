/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_its.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:24:30 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/25 15:33:40 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	is_parser_redir(t_parser **head)
{
	return (get_prev_non_space(get_last_parser(*head))->type == REDIR_OUTPUT
		|| get_prev_non_space(get_last_parser(*head))->type
		== REDIR_OUTPUT_APP
		|| get_prev_non_space(get_last_parser(*head))->type == REDIR_INPUT);
}

t_parser	*init_if_cmd(t_parser *lparser, t_parser **head, char *s, int x)
{
	t_parser	*new;

	new = NULL;
	if (get_prev_non_space(lparser) && is_parser_redir(head))
		new = parser_node_new(FILENAME, (s), x);
	if (get_prev_non_space(lparser) && (get_prev_non_space(lparser)->type
			== CMD_ARG || get_prev_non_space(lparser)->type == CMD))
			new = parser_node_new(CMD_ARG, (s), x);
	if (get_prev_non_space(lparser)
		&& get_prev_non_space(lparser)->type == DELIMITER)
		new = parser_node_new(IS_DELIMITER, (s), x);
	return (new);
}

int	its_command(t_parser **head, char *s, int *i)
{
	int			x;
	t_parser	*new;
	t_parser	*lparser;

	x = 0;
	lparser = get_last_parser(*head);
	while (s[x] && s[x] != ' ' && s[x] != '\t' && s[x] != '|' && s[x] != '<'
		&& s[x] != '>' && s[x] != '\'' && s[x] != '"' && s[x] != '$')
		x++;
	new = init_if_cmd(lparser, head, s, x);
	if (s[x] == '$' && ((s[x + 1] == '"'
				&& lparser->type == T_SPACE) || x == 0))
		*i += 1;
	if (s[x] == '$' && s[x + 1] == '"' && lparser->type == T_SPACE)
		return (1);
	if (*s == '$' && x == 0)
		new = parser_node_new(WAS_EXPANDED, (s), 1);
	if (new == NULL)
		new = parser_node_new(CMD, (s), x);
	if (new == 0)
		return (0);
	new_parser(head, new);
	*i += x;
	return (1);
}
