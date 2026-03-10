/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:31 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/10 17:56:37 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include <errno.h>

void	do_command_piped(t_program *program, t_commands *cmd,
	char *path, t_commands *first)
{
	char		*new_cmd;
	char		**args;
	char		**envp;
	struct stat	path_stat;

	if (cmd->cmd->type == DELIMITER)
	{
		free_t_commands_and_args(first);
		free_t_program(program);
		exit(1);
	}
	new_cmd = find_command(cmd->cmd->s, path);
	args = ft_dup_matrix(cmd->args);
	if (!args || !new_cmd)
	{
		free_t_commands_and_args(first);
		exit_check_args_cmd(program, args, new_cmd);
	}
	if (stat(new_cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		handle_is_dir(cmd, first, program, args);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	envp = program->envp;
	free_t_program(program);
	execve(new_cmd, args, envp);
	handle_execve_error(cmd, new_cmd, args, first);
}

static char	**prepare_cmd_args(t_parser *cmd, t_program *prog)
{
	char	**splited_cmd;

	splited_cmd = malloc(sizeof(char *) * (count_cmd_args(cmd) + 2));
	if (!splited_cmd)
		exit(1);
	splited_cmd = provision_commands(cmd, splited_cmd);
	if (!splited_cmd)
		clean_exit(prog, NULL, 127);
	return (splited_cmd);
}

static char	*find_and_check_cmd(t_parser *cmd, char *path,
	char **splited_cmd, t_program *prog)
{
	char		*new_cmd;
	struct stat	path_stat;

	new_cmd = find_command(cmd->s, path);
	if (!new_cmd)
	{
		if (errno == EACCES)
			clean_exit(prog, splited_cmd, 126);
		clean_exit(prog, splited_cmd, 127);
	}
	if (stat(new_cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		free(new_cmd);
		error_message_is_a_directory(cmd->s);
		clean_exit(prog, splited_cmd, 126);
	}
	return (new_cmd);
}

void	do_command(t_program *program, t_parser *cmd, char *path, char **envp)
{
	char		**splited_cmd;
	char		*new_cmd;

	splited_cmd = prepare_cmd_args(cmd, program);
	new_cmd = find_and_check_cmd(cmd, path, splited_cmd, program);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	close(program->saved_stdin);
	close(program->saved_stdout);
	execve(new_cmd, splited_cmd, envp);
	if (errno == EACCES || errno == ENOEXEC)
	{
		perror(cmd->s);
		clean_exit(program, splited_cmd, 126);
	}
	clean_exit(program, splited_cmd, 127);
}
