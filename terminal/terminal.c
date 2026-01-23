/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:04:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/23 17:55:20 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	main(void)
{
	char	*line;
	while (1)
	{
		line = readline("$miniswag>");
		if (!line)
				break ;
		if (line && *line)
		{
			add_history(line);
			t_parser *test = parsing(line);
			char *str;
			if (!test)
			{
				printf("syntax error\n");
				return (1);
			}
			while (test)
			{
				if (test->type == CMD)
					str = "CMD";
				else if (test->type == REDIR_OUTPUT)
					str = "REDIR_OUTPUT";
				else if (test->type == FILENAME)
					str = "FILENAME";
				else if (test->type == CMD_ARG)
					str = "CMD_ARG";
				else if (test->type == ENVVAR)
					str = "ENVVAR";
				else if (test->type == SQUOTE)
					str = "SQUOTE";
				else if (test->type == DQUOTE)
					str = "DQUOTE";
				else if (test->type == PIPE)
					str = "PIPE";
				else if (test->type == EXIT_STATUS)
					str = "EXIT_STATUS";
				else if (test->type == REDIR_INPUT)
					str = "REDIR_INPUT";
				else if (test->type == DELIMITER)
					str = "DELIMITER";
				else if (test->type == REDIR_OUTPUT_APP)
					str = "REDIR_OUTPUT_APP";
				else
					str = "OTHER ?????";
				printf("Type: %s | Str: %s\n", str, test->s);
				test = test->next;
			}
			free(line);
		}
	}
	return (0);
}