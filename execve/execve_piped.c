/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:16:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/12 15:50:33 by abarthes         ###   ########.fr       */
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
		do_command_piped(program, cmd, path, program->envp);
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
	//int		fd;

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
		// if (cmd->infile)
		// {
		// 	fd = open(cmd->infile, O_RDONLY);
		// 	if (fd < 0)
		// 	{
		// 		ft_printf_fd(2,
		// 			"miniswag: %s: No such file or directory", cmd->infile);
		// 		buildin_exit(program);
		// 		return ;
		// 	}
		// 	dup2(pipe_fd[0], STDIN_FILENO);
		// 	close(fd);
		// }
		handle_the_child(pipe_fd, program, cmd);
	}
}

int		setinputs(t_commands *commands, int pipe_fd[2])
{
	int	fd;

	dup2(pipe_fd[0], STDIN_FILENO);
	//check with get_last_input_node to handle HEREDOC redirections
	if (commands->inputtype == DELIMITER)
		return (0);
	if (commands->infile)
	{
		fd = open(commands->infile, O_RDONLY);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int		setoutputs(t_commands *commands, int pipe_fd[2])
{
	int	fd;

    //remove errors from makefile
	(void) pipe_fd;
	fd = 0;
	////
	if (commands->inputtype == DELIMITER)
		return (0);
	if (commands->outfile)
	{
		//TODO: Handle the different type of redir type to change the opening type
		if (commands->redir_type == REDIR_OUTPUT)
			fd = open(commands->infile, O_WRONLY, 0644);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

void	piped_exec(t_program *program, t_commands *commands)
{
	pid_t	pid;
	int		pipe_fd[2];

	//remove errors from makefile
	//setinputs(commands, &pipe_fd);
	//setoutputs();
	//
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
		get_path_for_exec(commands, program);
	}
}

int	execve_with_pipe(t_program *program)
{
	t_commands	*commands;

	commands = NULL;
	parse_commands_with_pipe(&commands, *(program->parsed));
	// while (commands)
	// {
	// 	ft_printf_fd(1, "command: %s\n", commands->cmd->s);
	// 	ft_printf_fd(1, "infile (if any): %s\n", commands->infile);
	// 	ft_printf_fd(1, "outfile (if any): %s\n", commands->outfile);
	// 	commands = commands->next;
	// }
	// return (0);
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
