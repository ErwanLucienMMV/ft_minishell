/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:26 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 14:47:56 by emaigne          ###   ########.fr       */
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

int	buildin_cd(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	char	*home;

	home = get_env_value_by_key(&envpath, "HOME");
	if (!cmd->next || cmd->next->type != CMD_ARG)
	{
		if (chdir(home) != 0)
			return (perror("cd"), program->last_exit_status = 1, 1);
		update_pwd_and_oldpwd(envpath);
		program->last_exit_status = 0;
		return (0);
	}
	else
	{
		if (chdir(cmd->next->s) != 0)
			return (perror("cd"), program->last_exit_status = 1, 1);
		update_pwd_and_oldpwd(envpath);
		program->last_exit_status = 0;
		return (0);
	}
}

int	check_buildin_piped(t_parser *cmd, t_envpath *envpath, t_program *program)
{
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

int	check_buildin(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	if (cmd->type == CMD && ft_strncmp(cmd->s, "exit", 4) == 0
		&& ft_strlen(cmd->s) == 4)
		return (buildin_exit(program));
	make_redirection(*program->parsed);
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

int	buildins(t_parser **parser, t_envpath *envpath, t_program *program)
{
	t_parser	*temp;

	if (!parser || !*parser)
		return (0);
	temp = *(program->parsed);
	if (check_buildin(temp, envpath, program))
		return (1);
	return (0);
}
