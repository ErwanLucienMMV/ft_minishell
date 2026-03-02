/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:12:57 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/02 16:27:13 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

extern volatile sig_atomic_t	g_signal;

void	sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(2, "\n", 1);
	}
}

void	create_signal(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler_heredoc;
	sigaction(SIGINT, &act, NULL);
}

int	handle_signal(t_program *program, int fd, char *line)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		program->last_exit_status = 130;
		if (line)
			free(line);
		close(fd);
		return (1);
	}
	return (0);
}
