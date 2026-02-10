/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_envpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:15:48 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/10 16:57:28 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void static	free_array_of_double(char **array)
{
	free(array[0]);
	free(array[1]);
	free(array);
}

int	static	second_if_check(t_parser *cmd, t_program *program)
{
	if (cmd->next->s[0] == '=' || (!ft_isalpha(cmd->next->s[0]) && cmd->next->s[0] != '_'))
	{
		printf("export: %s: not a valid identifier\n", cmd->next->s);
		program->last_exit_status = 1;
		return (1);
	}
	program->last_exit_status = 0;
	return (0);
}

int	buildin_export(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	char	*key;
	char	*value;
	char	**array;

	if (!cmd->next)
		return (program->last_exit_status = 0, print_envpath_list_sorted(envpath));
	while (cmd->next && (cmd->next->type == CMD_ARG || cmd->next->type == CMD))
	{
		if (!second_if_check(cmd, program))
		{
			array = ft_split(cmd->next->s, '=');
			if (!array)
				return (1);
			key = ft_strdup(array[0]);
			if (!array[1] && ft_strchr(cmd->next->s, '='))
				value = ft_strdup("");
			else if (!array[1] && !ft_strchr(cmd->next->s, '='))
				value = 0;
			else
				value = ft_strdup(array[1]);
			free_array_of_double(array);
			if (!new_envpath(&envpath, key, value))
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	buildin_unset(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	t_parser	*temp;
	t_envpath	*env_temp;

	temp = cmd->next;
	while (temp && temp->type == CMD_ARG)
	{
		env_temp = envpath;
		while (env_temp)
		{
			if (ft_strncmp(env_temp->index, temp->s, ft_strlen(temp->s)) == 0)
			{
				envp_delone(env_temp);
				break ;
			}
			env_temp = env_temp->next;
		}
		temp = temp->next;
	}
	program->last_exit_status = 0;
	return (0);
}

int	buildin_env(t_program *program)
{
	if (get_env_value_by_key(program->envpath, "PATH") == NULL)
	{
		printf("minishell: env: No such file or directory\n");
		program->last_exit_status = 127;
		return (0);
	}
	program->last_exit_status = 0;
	print_envpath_list(*program->envpath, 0);
	return (0);
}
