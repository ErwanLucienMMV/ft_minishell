/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:16:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 08:13:23 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

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
		if (setinputs(cmd) == 1 || setoutputs(cmd) == 1)
			free_t_cmd_prgrm_exit(cmd, program);
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
		if (setinputs(cmd) == 1 || setoutputs(cmd) == 1)
			free_t_cmd_prgrm_exit(cmd, program);
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
		if (setinputs(cmd) == 1 || setoutputs(cmd) == 1)
			free_t_cmd_prgrm_exit(cmd, program);
		handle_the_child(program, cmd);
	}
}


int	execve_with_pipe(t_program *program)
{
	t_commands	*commands;

	commands = NULL;
	parse_commands_with_pipe(&commands, *(program->parsed));
	if (IS_DEBUG)
	{
		ft_printf_fd(2, "size of a t_command: %d\n", sizeof(t_commands));
		ft_printf_fd(2, "size of a t_program: %d\n", sizeof(t_program));
	}
	if (commands == NULL)
		return (1);
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
