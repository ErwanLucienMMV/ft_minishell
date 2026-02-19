/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:12:28 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/18 22:41:55 by emaigne          ###   ########.fr       */
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

char	*get_a_valid_name(void)
{
	char	*filename;
	char	*totry;
	char	*it;

	totry = ft_strdup(".heredoc_temp_file");
	if (totry == NULL)
		return (NULL);
	it = ft_strdup("0");
	if (it == NULL)
		return (free(totry), NULL);
	while (1)
	{
		it[0] += 1;
		filename = ft_strjoin(totry, it);
		if (!filename)
			return (free(totry), free(it), NULL);
		if (access(filename, F_OK) == -1)
			return (free(totry), free(it), filename);
		free(filename);
		filename = NULL;
	}
	return (NULL);
}
//check with aurelien how does heredoc works and what kind of t_parser its expecting
int	check_for_redirections(t_parser *cmd, t_commands *tofill)
{
	t_parser	*temp;

	temp = cmd;
	while (temp && temp->prev && temp->prev->type != PIPE)
		temp = temp->prev;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIR_INPUT && temp->next)
		{
			free(tofill->infile);
			tofill->infile = ft_strdup(temp->next->s);
			if (!tofill->infile)
				return (1);
			if (access(tofill->infile, F_OK | R_OK) != 0)
				return (1);
		}
		if (temp->type == DELIMITER && temp->next)
		{
			free(tofill->infile);
			tofill->infile = get_a_valid_name();
			//ft_printf_fd(2, tofill->infile);
			doing_here_doc(&cmd, tofill->infile);
		}
		if ((temp->type == REDIR_OUTPUT
				|| temp->type == REDIR_OUTPUT_APP) && temp->next)
		{
			free(tofill->outfile);
			tofill->outfile = ft_strdup(temp->next->s);
			if (!tofill->outfile)
				return (1);
			tofill->redir_type = temp->type;
		}
		temp = temp->next;
	}
	return (0);
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
				return ;
			commands_add_back(commands, new_cmd);
			while (temp && temp->type != PIPE)
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
}
