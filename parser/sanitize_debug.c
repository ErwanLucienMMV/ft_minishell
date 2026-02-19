/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 23:40:05 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/19 22:37:59 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*check_error(t_parser *temp)
{
	char	*str;

	str = NULL;
	if (temp->type == CMD)
		str = "CMD";
	else if (temp->type == REDIR_OUTPUT)
		str = "REDIR_OUTPUT";
	else if (temp->type == FILENAME)
		str = "FILENAME";
	else if (temp->type == CMD_ARG)
		str = "CMD_ARG";
	else if (temp->type == ENVVAR)
		str = "ENVVAR";
	else if (temp->type == SQUOTE)
		str = "SQUOTE";
	else if (temp->type == DQUOTE)
		str = "DQUOTE";
	else if (temp->type == PIPE)
		str = "PIPE";
	else if (temp->type == EXIT_STATUS)
		str = "EXIT_STATUS";
	else if (temp->type == REDIR_INPUT)
		str = "REDIR_INPUT";
	else if (temp->type == REDIR_OUTPUT_APP)
		str = "REDIR_OUTPUT_APP";
	return (str);
}

void	print_error(t_parser *temp)
{
	char	*str;

	str = NULL;
	if (IS_DEBUG)
	{
		ft_printf_fd(2, "sanitizing..\n");

		while (temp)
		{
			str = check_error(temp);
			if (!str)
			{
				if (temp->type == DELIMITER)
					str = "DELIMITER";
				else if (temp->type == IS_DELIMITER)
					str = "IS_DELIMITER";
				else if (temp->type == T_SPACE)
					str = "T_SPACE";
				else
					str = "OTHER ?????";
			}
			printf("Type: %s | Str: %s\n", str, temp->s);
			temp = temp->next;
		}
	}
}
