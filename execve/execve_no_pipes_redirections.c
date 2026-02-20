/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_no_pipes_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:31:31 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:31:51 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include "../signals/signals.h"

static int	handle_output_redirection(t_parser *last_file_output)
{
	int	fd;

	if (!last_file_output)
		return (0);
	fd = open(last_file_output->s, O_WRONLY);
	if (fd < 0)
		return (error_message_file_not_found(last_file_output->s), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_input_redirection(t_parser *last_file_input)
{
	int	fd;

	if (!last_file_input)
		return (0);
	fd = open(last_file_input->s, O_RDONLY);
	if (fd < 0)
		return (error_message_file_not_found(last_file_input->s), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

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
	t_parser	*last_file_output;
	t_parser	*last_file_input;
	t_lexer		input_type;

	last_file_output = get_last_output_file(&parsed);
	last_file_input = get_last_input_node(parsed, &input_type);
	if (handle_output_redirection(last_file_output))
		return (1);
	if (input_type == REDIR_INPUT)
		return (handle_input_redirection(last_file_input));
	if (input_type == DELIMITER)
		return (handle_heredoc_redirection());
	return (0);
}
