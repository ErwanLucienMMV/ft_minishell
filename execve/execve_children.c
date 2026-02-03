/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:20:42 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/03 21:21:13 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	handle_middle_child(t_program *program, t_commands *cmd, int pipe_fd[2])
{
	char	*path;

	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if (is_a_buildin(cmd->cmd->s))
		check_buildin(cmd->cmd, *program->envpath, program);
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(cmd, path, program->envp);
	}
}
