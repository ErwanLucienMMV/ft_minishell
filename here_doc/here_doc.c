/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:30:51 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/06 12:28:28 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static int	is_only_delimiter(t_parser *lr, char *line)
{
	if ((ft_strlen(line) == ft_strlen(lr->next->s)
			&& !ft_strncmp(line, lr->next->s, ft_strlen(lr->next->s) + 1)))
	{
		free(line);
		return (1);
	}
	return (0);
}

static char	*read_heredoc_line(void)
{
	char	*line;
	size_t	len;

	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	doing_here_doc_util(t_program *p, t_parser *lr, char *tempfile, int mode)
{
	int					fd;
	char				*line;

	create_signal();
	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("here_doc: open"), -1);
	while (1)
	{
		line = read_heredoc_line();
		if (handle_signal(p, fd, line))
			return (1);
		if (!line)
		{
			error_message_error_heredoc(lr->next->s);
			break ;
		}
		else if (is_only_delimiter(lr, line))
			break ;
		if (mode == 1)
			line = expand_line(p, line, lr);
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (get_next_line(-1), close(fd), 0);
}

int	checking_is_delimiter(t_parser *temp, int *mode)
{
	if (!temp->next || !temp->next->s)
		return (ft_printf_fd(2,
				"miniswag: synthax error, asked for heredoc with no delimiter\n")
			, 1);
	if (ft_strchr(temp->next->s, '"') || ft_strchr(temp->next->s, '\''))
		*mode = 0;
	if (ft_strchr(temp->next->s, '"'))
	{
		if (!search_and_replace(temp->next, '"'))
			return (1);
	}
	if (ft_strchr(temp->next->s, '\''))
	{
		if (!search_and_replace(temp->next, '\''))
			return (1);
	}
	return (0);
}

int	doing_here_doc(t_program *program, char *tempfile)
{
	t_parser	*temp;
	int			mode;

	temp = *program->parsed;
	mode = 1;
	while (temp)
	{
		if (temp->type == DELIMITER)
		{
			if (checking_is_delimiter(temp, &mode))
				return (1);
			if (doing_here_doc_util(program, temp, tempfile, mode) == 1)
				return (1);
		}
		mode = 1;
		temp = temp->next;
	}
	get_next_line(-1);
	enable_echoctl();
	return (0);
}
