/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:16:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/06 14:42:06 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	get_path_for_exec(t_commands *cmd, t_program *program)
{
	char	*path;

	if (is_a_buildin(cmd->cmd->s))
		exit(check_buildin(cmd->cmd, *program->envpath, program));
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(cmd, path, program->envp);
	}
}

void	last_exec(t_program *program, t_commands *cmd)
{
	pid_t		pid;
	int			fd;
	t_parser	*file;

	pid = fork();
	if (pid == -1)
		return (perror("pid"), exit(1));
	if (pid != 0)
		return ;
	file = get_last_output_file(program->parsed);
	if (!file)
		fd = program->saved_stdout;
	else
		fd = open(file->s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	if (fd == 0)
		fd = program->saved_stdout;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	get_path_for_exec(cmd, program);
}

void	middle_exec(t_program *program, t_commands *cmd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) != 0)
		return (perror("pipe"), exit (1));
	pid = fork();
	if (pid == -1)
		return (perror("pid"), close(pipe_fd[0]), close(pipe_fd[1]),
			exit(1));
	if (pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	else
	{
		handle_middle_child(program, cmd, pipe_fd);
	}
}

void	first_exec(t_program *program, t_commands *cmd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) != 0)
		return (perror("pipe"), exit (1));
	pid = fork();
	if (pid == -1)
		return (perror("pid"), close(pipe_fd[0]), close(pipe_fd[1]),
			exit(1));
	if (pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	else
	{
		handle_the_child(pipe_fd, program, cmd);
	}
}


int	execve_with_pipe(t_program *program)
{
	int			status;
	t_commands	*commands;

	commands = NULL;
	status = 0;
	parse_commands_with_pipe(&commands, *(program->parsed));
	first_exec(program, commands);
	commands = commands->next;
	while (commands && commands->next)
	{
		middle_exec(program, commands);
		commands = commands->next;
	}
	last_exec(program, commands);
	waitpid(-1, &status, 0);
	program->last_exit_status = status;
	return (status);
}
