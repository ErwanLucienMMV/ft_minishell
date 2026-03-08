/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_no_pipes_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:31:31 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/08 01:15:06 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include "../signals/signals.h"

static int	handle_heredoc_redirection(void)
{
	int	fd;

	fd = open(HERE_DOC_TMPFILE, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: heredoc");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	make_redirection(t_parser *parsed)
{
	t_parser	*temp;

	temp = parsed;
	while (temp)
	{
		if (temp->type == REDIR_INPUT && temp->next)
		{
			if (open_and_set_input(temp->next->s))
				return (1);
		}
		else if (temp->type == DELIMITER)
		{
			if (handle_heredoc_redirection())
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
