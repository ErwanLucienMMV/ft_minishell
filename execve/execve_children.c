/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:20:42 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/26 14:55:14 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	handle_middle_child(t_program *program, t_commands *cmd,
	t_commands *first)
{
	char	*path;
	int		exitcode;

	if (is_a_buildin(cmd->cmd->s))
	{		
		if (is_exit(cmd->cmd->s))
		{
			exit_piped(program, cmd, first);
		}
		exitcode = check_buildin_piped(cmd->cmd,
				*program->envpath, program);
		free_t_commands_and_args(first);
		free_t_program(program);
		exit(exitcode);
	}
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(program, cmd, path, first);
	}
}

void	handle_the_child(t_program *program, t_commands *cmd, t_commands *first)
{
	char		*path;
	int			exitcode;

	if (is_a_buildin(cmd->cmd->s))
	{
		if (is_exit(cmd->cmd->s))
		{
			exit_piped(program, cmd, first);
		}
		exitcode = check_buildin_piped(cmd->cmd, *program->envpath, program);
		free_t_commands_and_args(first);
		free_t_program(program);
		exit(exitcode);
	}
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(program, cmd, path, first);
	}
}
