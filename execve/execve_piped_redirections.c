/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:51:09 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/10 18:01:44 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

static int	process_redirections(t_parser *temp)
{
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIR_INPUT && temp->next)
		{
			if (open_and_set_input(temp->next->s))
				return (1);
		}
		else if ((temp->type == REDIR_OUTPUT
				|| temp->type == REDIR_OUTPUT_APP) && temp->next)
		{
			if (open_and_set_output(temp->next->s, temp->type))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static int	handle_delimiter(t_commands *commands)
{
	if (commands->inputtype == DELIMITER && commands->infile)
	{
		if (open_and_set_input(commands->infile))
			return (1);
		if (unlink(commands->infile) < 0)
			return (perror("unlink"), 1);
	}
	return (0);
}

int	setinputs(t_commands *commands)
{
	t_parser	*temp;

	if (!commands || !commands->cmd)
		return (0);
	temp = commands->cmd;
	while (temp && temp->prev && temp->prev->type != PIPE)
		temp = temp->prev;
	if (process_redirections(temp))
		return (1);
	return (handle_delimiter(commands));
}

int	setoutputs(t_commands *commands)
{
	(void)commands;
	return (0);
}
