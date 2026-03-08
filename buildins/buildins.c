/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:26 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 00:39:34 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

extern volatile sig_atomic_t	g_signal;

int	buildin_pwd(t_program *program)
{
	char	cwd[1024];

	program->last_exit_status = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("getcwd() error");
		return (1);
	}
}

int	check_buildin_piped(t_parser *cmd, t_envpath *envpath,
	t_program *program)
{
	delete_redirections(program);
	if (cmd->type == CMD && ft_strncmp(cmd->s, "cd", 2) == 0
		&& ft_strlen(cmd->s) == 2)
		return (buildin_cd(cmd, envpath, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "echo", 4) == 0
		&& ft_strlen(cmd->s) == 4)
		return (buildin_echo(cmd, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "exit", 4) == 0
		&& ft_strlen(cmd->s) == 4)
		return (buildin_exit(program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "export", 6) == 0
		&& ft_strlen(cmd->s) == 6)
		return (buildin_export(cmd, envpath, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "unset", 5) == 0
		&& ft_strlen(cmd->s) == 5)
		return (buildin_unset(cmd, envpath, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "pwd", 3) == 0
		&& ft_strlen(cmd->s) == 3)
		return (buildin_pwd(program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "env", 3) == 0
		&& ft_strlen(cmd->s) == 3)
		return (buildin_env(program));
	return (0);
}

static int	execute_buildin_cmd(t_parser *cmd, t_envpath *envpath,
	t_program *program)
{
	if (cmd->type == CMD && ft_strncmp(cmd->s, "cd", 2) == 0
		&& ft_strlen(cmd->s) == 2)
		return (buildin_cd(cmd, envpath, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "echo", 4) == 0
		&& ft_strlen(cmd->s) == 4)
		return (buildin_echo(cmd, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "export", 6) == 0
		&& ft_strlen(cmd->s) == 6)
		return (buildin_export(cmd, envpath, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "unset", 5) == 0
		&& ft_strlen(cmd->s) == 5)
		return (buildin_unset(cmd, envpath, program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "pwd", 3) == 0
		&& ft_strlen(cmd->s) == 3)
		return (buildin_pwd(program));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "env", 3) == 0
		&& ft_strlen(cmd->s) == 3)
		return (buildin_env(program));
	return (0);
}

int	check_buildin(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	if (cmd->type == CMD && ft_strncmp(cmd->s, "exit", 4) == 0
		&& ft_strlen(cmd->s) == 4)
		return (buildin_exit(program));
	if (!(cmd->type == CMD && is_a_buildin(cmd->s)))
		return (0);
	if (make_redirection(*program->parsed))
	{
		program->last_exit_status = 1;
		delete_redirections(program);
		return (1);
	}
	delete_redirections(program);
	return (execute_buildin_cmd(cmd, envpath, program));
}

int	buildins(t_parser **parser, t_envpath *envpath, t_program *program)
{
	t_parser	*temp;

	if (!parser || !*parser)
		return (0);
	temp = *(program->parsed);
	if (temp->type == CMD && is_a_buildin(temp->s))
	{
		check_buildin(temp, envpath, program);
		return (1);
	}
	return (0);
}
