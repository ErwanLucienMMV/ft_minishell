/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:12:28 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/10 19:07:54 by abarthes         ###   ########.fr       */
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

char	**create_cmd_args(t_parser *cmd)
{
	int			j;
	int			i;
	char		**args;

	j = 0;
	i = parse_count_cmd_args(cmd);
	args = malloc((i + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	while (cmd && (cmd->type == CMD || cmd->type == CMD_ARG))
	{
		args[j] = malloc((ft_strlen(cmd->s) + 1) * sizeof(char));
		if (!args[j])
			return (free_incomplete_matrix(args, j));
		ft_strlcpy(args[j++], cmd->s, ft_strlen(cmd->s) + 1);
		cmd = cmd->next;
	}
	args[j] = NULL;
	return (args);
}

t_commands	*commands_node_new(t_parser *cmd, t_program *program)
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
	{
		free(new);
		return (NULL);
	}
	if (check_for_redirections(cmd, new, program) == 1)
	{
		clearmatrix(new->args);
		free(new);
		return (NULL);
	}
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

void	parse_commands_with_pipe(t_commands **commands,
		t_parser *parsed, t_program *program)
{
	t_parser	*segment_start;
	t_parser	*cmd_start;
	t_commands	*new_cmd;

	*commands = NULL;
	while (parsed)
	{
		segment_start = parsed;
		while (parsed && parsed->type != PIPE)
			parsed = parsed->next;
		cmd_start = find_cmd_start_in_segment(segment_start, parsed);
		if (cmd_start)
		{
			new_cmd = commands_node_new(cmd_start, program);
			if (!new_cmd)
			{
				free_all_commands(commands);
				*commands = NULL;
				return ;
			}
			commands_add_back(commands, new_cmd);
		}
		if (parsed)
			parsed = parsed->next;
	}
}
