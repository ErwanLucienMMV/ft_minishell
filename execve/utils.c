/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:31 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 01:37:05 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"

void	do_command_piped(t_program *program, t_commands *cmd,
	char *path, char **envp)
{
	char		*new_cmd;

	if (cmd->cmd->type == DELIMITER)
		exit(1);
	new_cmd = find_command(cmd->cmd->s, path);
	if (!new_cmd)
	{
		free_t_command(cmd);
		free_t_program(program);
		exit (1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	execve(new_cmd, cmd->args, envp);
	error_message_command_not_found(cmd->cmd->s);
	free(new_cmd);
	exit(127);
}

void	do_command(t_program *program, t_parser *cmd, char *path, char **envp)
{
	char		**splited_cmd;
	char		*new_cmd;
	t_parser	*temp;
	int			i;

	i = 1;
	splited_cmd = malloc(sizeof(char *) * (count_cmd_args(cmd) + 2));
	if (!splited_cmd)
		exit(1);
	splited_cmd[0] = cmd->s;
	temp = cmd->next;
	while (temp && temp->type == CMD_ARG)
	{
		splited_cmd[i++] = temp->s;
		temp = temp->next;
	}
	splited_cmd[i] = NULL;
	new_cmd = find_command(cmd->s, path);
	if (!new_cmd)
		clean_exit(splited_cmd, NULL);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	execve(new_cmd, splited_cmd, envp);
	error_message_command_not_found(cmd->s);
	clean_exit(splited_cmd, new_cmd);
}
