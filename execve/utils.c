/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:31 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/11 08:46:08 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"

void	clearmatrix(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = 0;
		i++;
	}
	free(tab);
}

void	do_command_piped(t_program *program, t_commands *cmd, char *path, char **envp)
{
	char		*new_cmd;

	if (cmd->cmd->type == DELIMITER)
		exit(1);
	new_cmd = find_command(cmd->cmd->s, path);
	ft_printf_fd(2, "Command path: %s", new_cmd);
	if (!new_cmd)
		exit (1);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	execve(new_cmd, cmd->args, envp);
	perror("execve:");
	free(new_cmd);
	exit(1);
}

void	handle_the_child(int pipe_fd[2], t_program *program, t_commands *cmd)
{
	int			fd;
	char		*path;
	t_parser	*file;
	t_lexer		input_type;

	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	file = get_last_input_node(*(program->parsed), &input_type);
	if (input_type == REDIR_INPUT && file)
		fd = open(file->s, O_RDONLY);
	else if (input_type == DELIMITER)
		fd = open(HERE_DOC_TMPFILE, O_RDONLY);
	else
		fd = program->saved_stdin;
	if (fd < 0)
	{
		perror("open"); 
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (is_a_buildin(cmd->cmd->s))
		exit(check_buildin(cmd->cmd, *program->envpath, program));
	else
	{
		path = get_env_value_by_key(program->envpath, "PATH");
		do_command_piped(program, cmd, path, program->envp);
	}
}

void	clean_exit(char **splited_cmd, char *new_cmd)
{
	if (splited_cmd)
		clearmatrix(splited_cmd);
	if (new_cmd)
		free(new_cmd);
	exit(1);
}

void	do_command(t_program *program, t_parser *cmd, char *path, char **envp)
{
	char		**splited_cmd;
	char		*new_cmd;
	t_parser	*temp;
	int			i;

	i = 1;
	splited_cmd = malloc(sizeof(char *) * (count_cmd_args(cmd) + 2));
	if (!splited_cmd)
		exit(1);
	splited_cmd[0] = cmd->s;
	temp = cmd->next;
	while (temp && temp->type == CMD_ARG)
	{
		splited_cmd[i++] = temp->s;
		temp = temp->next;
	}
	splited_cmd[i] = NULL;
	new_cmd = find_command(cmd->s, path);
	if (!new_cmd)
		clean_exit(splited_cmd, NULL);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	execve(new_cmd, splited_cmd, envp);
	perror("execve:");
	clean_exit(splited_cmd, new_cmd);
}
