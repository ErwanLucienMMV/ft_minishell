/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:40:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 16:29:46 by abarthes         ###   ########.fr       */
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
		printf("miniswag: cd: OLDPWD not set\n");
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
		printf("minishell: cd: HOME not set\n");
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
	else if (ft_strncmp(cmd->next->s, "~", 2) == 0)
		return (cd_no_arg_case(envpath, program));
	else if (ft_strncmp(cmd->next->s, "-", 2) == 0)
		return (cd_dash_case(envpath, program));
	else
		return (cd_arg_case(cmd, envpath, program));
}
