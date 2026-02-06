/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:44:15 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/06 12:59:12 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

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

void	exec_one_command(t_parser *cmd, char *path, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("pid"), exit(1));
	if (pid)
		return ;
	else
		do_command(cmd, path, envp);
}

int	make_redirection(t_parser *parsed)
{
	t_parser	*last_file_output;
	t_parser	*last_file_input;
	int			fd;

	last_file_output = get_last_output_file(&parsed);
	last_file_input = get_last_input_file(&parsed);
	if (last_file_output)
	{
		fd = open(last_file_output->s, O_WRONLY);
		if (fd < 0)
		{
			char src[1024] = "minishell: ";
			ft_strlcat(src, last_file_output->s, 1010);
			perror(src);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (last_file_input)
	{
		fd = open(last_file_input->s, O_RDONLY);
		if (fd < 0)
		{
			char src[1024] = "minishell: ";
			ft_strlcat(src, last_file_input->s, 1010);
			perror(src);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	execve_without_pipe(t_parser **parsed, t_envpath *envpath, char **envp)
{
	t_parser	*cmd;

	cmd = get_first_cmd_no_buildins(*parsed);
	if (!cmd)
		return (1);
	make_redirection(*parsed);
	exec_one_command(cmd, get_env_value_by_key(&envpath, "PATH"), envp);
	return (0);
}

// int	execve_handler(t_parser **lineread, t_envpath *envpath, char **envp)
int	execve_handler(t_program *program)
{
	int	status;

	status = 0;
	if (there_is_at_least_one_pipe(*(program->parsed)))
	{
		if (execve_with_pipe(program))
			return (1);
	}
	else
	{
		if (execve_without_pipe(program->parsed,
				*(program->envpath), program->envp))
			return (1);
	}
	waitpid(-1, &status, 0);
	program->last_exit_status = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
