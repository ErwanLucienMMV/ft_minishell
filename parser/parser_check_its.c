/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_its.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:24:30 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 15:17:43 by abarthes         ###   ########.fr       */
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

int	its_command(t_parser **head, char *s, int *i)
{
	int			x;
	t_parser	*new;

	x = 0;
	new = NULL;
	while (s[x] && s[x] != ' ' && s[x] != '\t' && s[x] != '|' && s[x] != '<'
		&& s[x] != '>' && s[x] != '\'' && s[x] != '"' && s[x] != '$')
		x++;
	if (get_prev_non_space(get_last_parser(*head)) && is_parser_redir(head))
		new = parser_node_new(FILENAME, (s), x);
	if (get_prev_non_space(get_last_parser(*head)) && (
		get_prev_non_space(get_last_parser(*head))->type == CMD_ARG
		|| get_prev_non_space(get_last_parser(*head))->type == CMD))
			new = parser_node_new(CMD_ARG, (s), x);
	if (get_prev_non_space(get_last_parser(*head))
		&& get_prev_non_space(get_last_parser(*head))->type == DELIMITER)
		new = parser_node_new(IS_DELIMITER, (s), x);
	if (new == NULL)
		new = parser_node_new(CMD, (s), x);
	if (new == 0)
		return (0);
	new_parser(head, new);
	*i += x;
	return (1);
}
