/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_its_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:35:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:06:29 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_dollar_quote(char *s, int x, t_parser *lparser, int *i)
{
	if (s[x] == '$' && ((s[x + 1] == '"'
				&& lparser->type == T_SPACE) || x == 0))
		*i += 1;
	if (s[x] == '$' && s[x + 1] == '"' && lparser->type == T_SPACE)
		return (1);
	return (0);
}

t_parser	*create_cmd_node(char *s, int x, t_parser *lparser, t_parser **head)
{
	t_parser	*new;
	t_parser	*prev;

	(void)head;
	if (*s == '$' && x == 0 && (*(s + 1) == '\'' || *(s + 1) == '"'))
		new = parser_node_new(CMD, (s), 1);
	else if (*s == '$' && x == 0)
		new = parser_node_new(WAS_EXPANDED, (s), 1);
	else
	{
		new = NULL;
		prev = get_prev_non_space(lparser);
		if (prev && (prev->type == REDIR_OUTPUT || prev->type
				== REDIR_OUTPUT_APP || prev->type == REDIR_INPUT))
			new = parser_node_new(FILENAME, (s), x);
		else if (prev && prev->type == DELIMITER)
			new = parser_node_new(IS_DELIMITER, (s), x);
		else if (prev && get_prev_cmd(lparser))
			new = parser_node_new(CMD_ARG, (s), x);
	}
	if (new == NULL)
		new = parser_node_new(CMD, (s), x);
	return (new);
}
