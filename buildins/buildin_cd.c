/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:40:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/09 11:46:49 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

static int	cd_arg_case(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	if (chdir(cmd->next->s) != 0)
		return (perror("cd"), program->last_exit_status = 1, 1);
	update_pwd_and_oldpwd(envpath);
	program->last_exit_status = 0;
	return (0);
}

static int	cd_dash_case(t_envpath *envpath, t_program *program)
{
	char	*oldpwd;

	oldpwd = get_env_value_by_key(&envpath, "OLDPWD");
	if (!oldpwd || !oldpwd[0])
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 29);
		program->last_exit_status = 1;
		return (1);
	}
	if (chdir(oldpwd) != 0)
		return (perror("cd"), program->last_exit_status = 1, 1);
	update_pwd_and_oldpwd(envpath);
	buildin_pwd(program);
	program->last_exit_status = 0;
	return (0);
}

static int	cd_no_arg_case(t_envpath *envpath, t_program *program)
{
	char	*home;

	home = get_env_value_by_key(&envpath, "HOME");
	if (!home)
	{
		write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		program->last_exit_status = 1;
		return (1);
	}
	if (chdir(home) != 0)
		return (perror("cd"), program->last_exit_status = 1, 1);
	update_pwd_and_oldpwd(envpath);
	program->last_exit_status = 0;
	return (0);
}

int	buildin_cd(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	if (!cmd->next || cmd->next->type != CMD_ARG)
		return (cd_no_arg_case(envpath, program));
	else if (cmd->next->type == CMD_ARG && cmd->next->next
		&& cmd->next->next->type == CMD_ARG)
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		program->last_exit_status = 1;
		return (1);
	}
	else if (ft_strncmp(cmd->next->s, "~", 2) == 0)
		return (cd_no_arg_case(envpath, program));
	else if (ft_strncmp(cmd->next->s, "-", 2) == 0)
		return (cd_dash_case(envpath, program));
	else
		return (cd_arg_case(cmd, envpath, program));
}
