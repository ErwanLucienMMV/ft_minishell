/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:12:28 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 06:22:37 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	commands_add_back(t_commands **lst, t_commands *new)
{
	t_commands	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

//a proteger prcq si malloc de args[j] fail on ne protege pas ni ne free pas
char	**create_cmd_args(t_parser *cmd)
{
	t_parser	*temp;
	int			j;
	int			i;
	char		**args;

	temp = cmd;
	j = 0;
	i = 0;
	while (temp && (temp->type == CMD || temp->type == CMD_ARG))
	{
		i++;
		temp = temp->next;
	}
	args = malloc((i + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	while (cmd && (cmd->type == CMD || cmd->type == CMD_ARG))
	{
		args[j] = malloc((ft_strlen(cmd->s) + 1) * sizeof(char));
		ft_strlcpy(args[j], cmd->s, ft_strlen(cmd->s) + 1);
		cmd = cmd->next;
		j++;
	}
	args[j] = NULL;
	return (args);
}

t_commands	*commands_node_new(t_parser *cmd)
{
	t_commands	*new;

	new = ft_calloc(1, sizeof(t_commands));
	if (!new)
		return (0);
	new->infile = NULL;
	new->outfile = NULL;
	new->cmd = cmd;
	new->args = create_cmd_args(cmd);
	if (!new->args)
		return (free_t_command(new), NULL);
	if (check_for_redirections(cmd, new) == 1)
		return (free_t_command(new), NULL);
	new->next = NULL;
	return (new);
}

void	free_all_commands(t_commands **commands)
{
	t_commands	*next;
	t_commands	*curr;

	if (!commands || !*commands)
		return ;
	next = (*commands)->next;
	curr = *commands;
	while (next)
	{
		free_t_command(curr);
		curr = next;
		next = curr->next;
	}
	free_t_command(curr);
}

void	parse_commands_with_pipe(t_commands **commands, t_parser *parsed)
{
	t_parser	*temp;
	t_commands	*new_cmd;

	*commands = NULL;
	temp = parsed;
	while (temp)
	{
		if (temp->type == CMD || temp->type == DELIMITER)
		{
			new_cmd = commands_node_new(temp);
			if (!new_cmd)
			{
				free_all_commands(commands);
				*commands = NULL;
				return ;
			}
			commands_add_back(commands, new_cmd);
			while (temp && temp->type != PIPE)
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
}
