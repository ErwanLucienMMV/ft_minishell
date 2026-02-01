/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:26 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/01 14:39:31 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	buildin_export(t_parser *cmd, t_envpath *envpath)
{
	char	*key;
	char	*value;

	if (!cmd->next)
		return (print_envpath_list_sorted(envpath));
	if (!cmd->next || cmd->next->type != CMD_ARG || !ft_strchr(cmd->next->s, '=') || cmd->next->s[0] == '=')
		return (1);
	if (!ft_isalpha(cmd->next->s[0]))
		return (1);
	if (cmd->next->next && (cmd->next->next->type == CMD_ARG || cmd->next->next->type == CMD))
	{
		key = ft_strtrim(cmd->next->s, "=");
		value = cmd->next->next->s;
	}
	else
	{
		char **array = ft_split(cmd->next->s, '=');
		printf("Split result: %s, %s\n", array[0], array[1]);
		if (!array || !array[0] || !array[1])
			return (1);
		key = ft_strdup(array[0]);
		value = ft_strdup(array[1]);
		free(array[0]);
		free(array[1]);
		free(array);
	}
	printf("Exporting key: %s with value: %s\n", key, value);
	if (!new_envpath(&envpath, key, value))
		return (1);
	return (0);
}

int	buildin_unset(t_parser *cmd, t_envpath *envpath)
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
	return (0);
}

int buildin_echo(t_parser *cmd)
{
	t_parser	*temp;
	int			is_n;


	is_n = 0;
	if (!cmd->next)
	{
		printf("\n");
		return (0);
	}
	temp = cmd->next;
	if (ft_strncmp(temp->s, "-n", 2) == 0)
	{
		is_n = 1;
		temp = temp->next;
	}
	while (temp && (temp->type == CMD || temp->type == CMD_ARG))
	{
		printf("%s", temp->s);
		temp = temp->next;
		if (temp)
			printf(" ");
	}
	if (!is_n)
		printf("\n");
	return (0);
}

int	buildin_exit(void)
{
	exit(0);
	return (0);
}

int	buildin_pwd(void)
{
	char	cwd[1024];

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

int	buildin_cd(t_parser *cmd, t_envpath *envpath)
{
	char	*home;

	home = get_env_value_by_key(envpath, "HOME");
	if (!cmd->next || cmd->next->type != CMD_ARG)
	{
		if (chdir(home) != 0)
			return (perror("cd"), 1);
		return (0);
	}
	else
	{
		if (chdir(cmd->next->s) != 0)
			return (perror("cd"), 1);
		return (0);
	}
}

int	check_buildin(t_parser *cmd, t_envpath *envpath)
{
	if (cmd->type == CMD && ft_strncmp(cmd->s, "cd", 2) == 0 && ft_strlen(cmd->s) == 2)
		return (buildin_cd(cmd, envpath));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "echo", 4) == 0 && ft_strlen(cmd->s) == 4)
		return (buildin_echo(cmd));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "exit", 4) == 0 && ft_strlen(cmd->s) == 4)
		return (buildin_exit());
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "export", 6) == 0 && ft_strlen(cmd->s) == 6)
		return (buildin_export(cmd, envpath));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "unset", 5) == 0 && ft_strlen(cmd->s) == 5)
		return (buildin_unset(cmd, envpath));
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "pwd", 3) == 0 && ft_strlen(cmd->s) == 3)
		return (buildin_pwd());
	else if (cmd->type == CMD && ft_strncmp(cmd->s, "env", 3) == 0 && ft_strlen(cmd->s) == 3)
		return (print_envpath_list(envpath, 0));
	return (0);
}

int	buildins(t_parser **parser, t_envpath *envpath)
{
	t_parser	*temp;

	if (!parser || !*parser)
		return (0);
	temp = *parser;
	if (check_buildin(temp, envpath))
		return (1);
	return (0);
}
