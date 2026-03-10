/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:14:52 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/10 12:27:05 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] == '=' || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*extract_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static int	process_export_arg(t_parser *cmd, t_envpath *envpath)
{
	char	*key;
	char	*equal_sign;

	equal_sign = ft_strchr(cmd->s, '=');
	if (!equal_sign)
	{
		if (!new_envpath(&envpath, cmd->s, NULL))
			return (0);
		return (1);
	}
	key = extract_key(cmd->s);
	if (!key)
		return (0);
	if (!new_envpath(&envpath, key, equal_sign + 1))
	{
		free(key);
		return (0);
	}
	free(key);
	return (1);
}

int	buildin_export(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	if (!cmd->next || cmd->next->type != CMD_ARG)
		return (program->last_exit_status = 0,
			print_envpath_list_sorted(envpath));
	cmd = cmd->next;
	program->last_exit_status = 0;
	while (cmd && cmd->type == CMD_ARG)
	{
		if (!is_valid_identifier(cmd->s))
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier\n", cmd->s);
			program->last_exit_status = 1;
		}
		else if (!process_export_arg(cmd, envpath))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	buildin_unset(t_parser *cmd, t_envpath *envpath, t_program *program)
{
	t_parser	*temp;

	(void)envpath;
	temp = cmd->next;
	while (temp && temp->type == CMD_ARG)
	{
		del_env_node_by_key(program->envpath, temp->s);
		temp = temp->next;
	}
	program->last_exit_status = 0;
	return (0);
}
