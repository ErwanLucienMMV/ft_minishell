/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:16:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/17 23:18:16 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

int	setinputs(t_commands *commands)
{
	int	fd;

	if (commands->inputtype == DELIMITER)
	{
		// find exactly the name of heredoc
		fd = open(commands->infile, O_RDONLY);
		if (fd < 0)
			return (perror("open"), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (commands->infile)
	{
		fd = open(commands->infile, O_RDONLY);
		if (fd < 0)
			return (perror("open"), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	setoutputs(t_commands *commands)
{
	int	fd;

	if (commands->outfile)
	{
		if (commands->redir_type == REDIR_OUTPUT_APP)
		{
			fd = open(commands->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			fd = open(commands->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open"), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

void	get_path_for_exec(t_commands *cmd, t_program *program)
{
	char	*path;

	if (is_a_buildin(cmd->cmd->s))
		exit(check_buildin_piped(cmd->cmd, *program->envpath, program));
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(program, cmd, path, program->envp);
	}
}

void	last_exec(t_program *program, t_commands *cmd)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (perror("pid"), exit(1));
	if (pid != 0)
		return ;
	else
	{
		setinputs(cmd);
		setoutputs(cmd);
		get_path_for_exec(cmd, program);
	}
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
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		setinputs(cmd);
		setoutputs(cmd);
		handle_middle_child(program, cmd);
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
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		setinputs(cmd);
		setoutputs(cmd);
		handle_the_child(pipe_fd, program, cmd);
	}
}

int	execve_with_pipe(t_program *program)
{
	t_commands	*commands;

	commands = NULL;
	parse_commands_with_pipe(&commands, *(program->parsed));
	first_exec(program, commands);
	commands = commands->next;
	while (commands && commands->next)
	{
		middle_exec(program, commands);
		commands = commands->next;
	}
	last_exec(program, commands);
	return (0);
}
