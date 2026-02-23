/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_piped_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:51:09 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 12:42:47 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

int    setinputs(t_commands *commands)
{
    int    fd;

    if (commands->infile)
    {
        fd = open(commands->infile, O_RDONLY);
        if (fd < 0)
            return (perror("open"), 1);
        dup2(fd, STDIN_FILENO);
        close(fd);
        if (commands->inputtype == DELIMITER)
            unlink(commands->infile);
    }
    return (0);
}

int	setoutputs(t_commands *commands)
{
	int	fd;

	if (commands->outfile)
	{
		if (commands->redir_type == REDIR_OUTPUT_APP)
		{
			fd = open(commands->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			fd = open(commands->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open"), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
