/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:20:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:06:02 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include <errno.h>

void	exit_check_args_cmd(t_program *program, char **args, char *new_cmd)
{
	if (!args)
	{
		free_t_program(program);
		clearmatrix(args);
		exit (1);
	}
	if (!new_cmd)
	{
		free_t_program(program);
		clearmatrix(args);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
}

void	handle_is_dir(t_commands *cmd, t_commands *first,
	t_program *program, char **args)
{
	error_message_is_a_directory(cmd->cmd->s);
	free_t_commands_and_args(first);
	free_t_program(program);
	clearmatrix(args);
	exit(126);
}

void	handle_execve_error(t_commands *cmd, char *new_cmd,
	char **args, t_commands *first)
{
	if (errno == EACCES || errno == ENOEXEC)
	{
		perror(cmd->cmd->s);
		free(new_cmd);
		clearmatrix(args);
		free_t_commands_and_args(first);
		exit(126);
	}
	perror(cmd->cmd->s);
	free(new_cmd);
	clearmatrix(args);
	free_t_commands_and_args(first);
	exit(127);
}
