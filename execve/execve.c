/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:44:15 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/18 21:46:42 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include "../signals/signals.h"

t_parser	*get_first_cmd_no_buildins(t_parser *cmd)
{
	t_parser	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->type == CMD && !is_a_buildin(temp->s))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	exec_one_command(t_program *program, t_parser *cmd, char *path, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("pid"), exit(1));
	if (pid)
		return ;
	else
		do_command(program, cmd, path, envp);
}

int	make_redirection(t_parser *parsed)
{
	t_parser	*last_file_output;
	t_parser	*last_file_input;
	t_lexer		input_type;
	int			fd;

	last_file_output = get_last_output_file(&parsed);
	last_file_input = get_last_input_node(parsed, &input_type);
	if (last_file_output)
	{
		fd = open(last_file_output->s, O_WRONLY);
		if (fd < 0)
			return (error_message_file_not_found(last_file_output->s), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (input_type == REDIR_INPUT && last_file_input)
	{
		fd = open(last_file_input->s, O_RDONLY);
		if (fd < 0)
			return (error_message_file_not_found(last_file_input->s), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (input_type == DELIMITER)
	{
		fd = open(HERE_DOC_TMPFILE, O_RDONLY);
		if (fd < 0)
		{
			perror("minishell: heredoc");
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	execve_without_pipe(t_program *program, t_parser **parsed, t_envpath *envpath, char **envp)
{
	t_parser	*cmd;

	cmd = get_first_cmd_no_buildins(*parsed);
	if (!cmd)
		return (1);
	make_redirection(*parsed);
	exec_one_command(program, cmd, get_env_value_by_key(&envpath, "PATH"), envp);
	return (0);
}

int	execve_handler(t_program *program)
{
	int	status;
	int	last_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (there_is_at_least_one_pipe(*(program->parsed)))
	{
		if (execve_with_pipe(program))
			return (1);
	}
	else
	{
		if (execve_without_pipe(program, program->parsed,
				*(program->envpath), program->envp))
			return (1);
	}
	last_status = 0;
	set_signal_action();
	while (waitpid(-1, &status, 0) > 0)
		last_status = WEXITSTATUS(status);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	program->last_exit_status = last_status;
	return (last_status);
}
