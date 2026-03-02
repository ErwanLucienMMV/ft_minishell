/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:03:53 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/02 16:19:16 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <unistd.h>

extern volatile sig_atomic_t	g_signal;

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(2, "\n", 1);
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTSTP, &act, NULL);
}

t_signal_handlers	setup_signals_before_fork(void)
{
	struct sigaction	sa;
	t_signal_handlers	handlers;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &handlers.old_int);
	sigaction(SIGQUIT, &sa, &handlers.old_quit);
	sigaction(SIGTSTP, &sa, &handlers.old_tstp);
	return (handlers);
}

void	setup_signals_after_fork(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	restore_signals(t_signal_handlers handlers)
{
	sigaction(SIGINT, &handlers.old_int, NULL);
	sigaction(SIGQUIT, &handlers.old_quit, NULL);
	sigaction(SIGTSTP, &handlers.old_tstp, NULL);
}
