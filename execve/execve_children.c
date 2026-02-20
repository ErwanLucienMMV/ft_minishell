/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:20:42 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 01:11:35 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	handle_middle_child(t_program *program, t_commands *cmd)
{
	char	*path;

	if (is_a_buildin(cmd->cmd->s))
		exit(check_buildin_piped(cmd->cmd, *program->envpath, program)); //free everything beside cmd->cmd
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(program, cmd, path, program->envp);
	}
}

void	handle_the_child(t_program *program, t_commands *cmd)
{
	char		*path;

	if (is_a_buildin(cmd->cmd->s))
		exit(check_buildin_piped(cmd->cmd, *program->envpath, program));
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(program, cmd, path, program->envp);
	}
}
