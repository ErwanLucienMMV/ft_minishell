/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped_redirections_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:25:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:06:02 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

int	open_and_set_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_message_file_not_found(filename), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	open_and_set_output(char *filename, t_lexer redir_type)
{
	int	fd;

	if (redir_type == REDIR_OUTPUT_APP)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (error_message_file_not_found(filename), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
