/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:04:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/31 13:44:43 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

volatile sig_atomic_t g_signal;

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*line;
	t_envpath	*envpath;

	envpath = NULL;
	if (create_envpath_list(&envpath, envp) == 0)
		return (1);
	while (1)
	{
		set_signal_action();
		line = readline("$miniswag> ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			if (line)
				free(line);
			continue;
		}
		if (!line)
			break ;
		if (line && *line)
		{
			add_history(line);
			t_parser *lineread = parsing(line);
			free(line);
			if (!lineread || !sanitize(&lineread))
				printf("syntax error\n");
			else
			{
				t_parser *temp = lineread;
				char *str;
				while (temp)
				{
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
					else if (temp->type == DELIMITER)
						str = "DELIMITER";
					else if (temp->type == IS_DELIMITER)
						str = "IS_DELIMITER";
					else
						str = "OTHER ?????";
					printf("Type: %s | Str: %s\n", str, temp->s);
					temp = temp->next;
				}
				//expand
				printf("After expansion:\n");
				send_to_expand(&lineread, envpath);
				temp = lineread;
				while (temp)
				{
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
					else if (temp->type == DELIMITER)
						str = "DELIMITER";
					else if (temp->type == IS_DELIMITER)
						str = "IS_DELIMITER";
					else
						str = "OTHER ?????";
					printf("Type: %s | Str: %s\n", str, temp->s);
					temp = temp->next;
				}
				// creation des fichiers
				// redirections
				int saved_stdin = dup(STDIN_FILENO);
				int saved_stdout = dup(STDOUT_FILENO);
				if (file_handler(&lineread))
				{
					if (saved_stdin >= 0)
					{
						dup2(saved_stdin, STDIN_FILENO);
						close(saved_stdin);
					}
					if (saved_stdout >= 0)
					{
						dup2(saved_stdout, STDOUT_FILENO);
						close(saved_stdout);
					}
					parser_clear(&lineread);
					continue ;
				}
				//buildin
				buildins(&lineread, envpath);
				if (saved_stdin >= 0)
				{
					dup2(saved_stdin, STDIN_FILENO);
					close(saved_stdin);
				}
				if (saved_stdout >= 0)
				{
					dup2(saved_stdout, STDOUT_FILENO);
					close(saved_stdout);
				}
				//execve
				parser_clear(&lineread);
			}
		}
	}
	return (0);
}
