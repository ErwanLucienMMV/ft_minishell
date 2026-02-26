/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:48:20 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/26 11:33:08 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

int	there_is_at_least_one_pipe(t_parser *lineread)
{
	t_parser	*temp;

	temp = lineread;
	while (temp)
	{
		if (temp->type == PIPE)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	count_cmd_args(t_parser *cmd)
{
	t_parser	*temp;
	int			count;

	count = 0;
	temp = cmd->next;
	while (temp && temp->type == CMD_ARG)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	is_a_buildin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}

t_parser	*get_last_input_node(t_parser *parsed, t_lexer *input_type)
{
	t_parser	*temp;
	t_parser	*last;

	*input_type = -1;
	last = NULL;
	temp = parsed;
	while (temp)
	{
		if (temp->type == REDIR_INPUT && temp->next)
		{
			last = temp->next;
			*input_type = REDIR_INPUT;
		}
		else if (temp->type == DELIMITER)
		{
			last = temp->next;
			*input_type = DELIMITER;
		}
		temp = temp->next;
	}
	return (last);
}

int	is_exit(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}
