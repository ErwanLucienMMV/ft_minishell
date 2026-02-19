/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:31:09 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/19 22:44:16 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

char static	*return_temp_type_helper(t_parser *temp)
{
	char	*str;

	str = NULL;
	if (temp->type == CMD_ARG)
			str = "CMD_ARG";
	else if (temp->type == ENVVAR)
		str = "ENVVAR";
	else if (temp->type == SQUOTE)
		str = "SQUOTE";
	else if (temp->type == DQUOTE)
		str = "DQUOTE";
	return (str);
}

char static	*return_temptype(t_parser *temp)
{
	char	*str;

	str = return_temp_type_helper(temp);
	if (str != NULL)
	{
		if (temp->type == PIPE)
			str = "PIPE";
		else if (temp->type == EXIT_STATUS)
			str = "EXIT_STATUS";
		else if (temp->type == REDIR_INPUT)
			str = "REDIR_INPUT";
		else if (temp->type == REDIR_OUTPUT_APP)
			str = "REDIR_OUTPUT_APP";
		else if (temp->type == DELIMITER)
			str = "DELIMITER";
		else if (temp->type == IS_DELIMITER)
			str = "IS_DELIMITER";
		else if (temp->type == T_SPACE)
			str = "SPACE";
		else if (temp->type == WAS_EXPANDED)
			str = "WAS_EXPANDED";
		else
			str = "OTHER ?????";
	}
	return (str);
}

void	print_debug(t_program *program)
{
	static int	state;
	t_parser	*temp;
	char		*str;

	if (IS_DEBUG == 1 && ft_printf_fd(2, "printing debug\n"))
	{
		if (state == 0)
			state = 1;
		else
			printf("After expansion:\n");
		temp = *(program->parsed);
		while (temp)
		{
			if (temp->type == CMD)
				str = "CMD";
			else if (temp->type == REDIR_OUTPUT)
				str = "REDIR_OUTPUT";
			else if (temp->type == FILENAME)
				str = "FILENAME";
			else
				str = return_temptype(temp);
			printf("Type: %s | Str: %s\n", str, temp->s);
			temp = temp->next;
		}
	}
}
