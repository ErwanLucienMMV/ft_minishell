/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:12:57 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/03 11:26:48 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include <termios.h>

#ifndef ECHOCTL
# define ECHOCTL 0x00000040
#endif

extern volatile sig_atomic_t	g_signal;

static void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(2, "^C\n", 3);
	}
}

void	create_signal(void)
{
	struct sigaction	act;

	disable_echoctl();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler_heredoc;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
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
		enable_echoctl();
		return (1);
	}
	return (0);
}
