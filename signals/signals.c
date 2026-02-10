/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:03:53 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/10 13:58:42 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <unistd.h>

extern volatile sig_atomic_t	g_signal;

// a completer le signal == SIGQUIT
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
	// else if (signal == SIGQUIT)
	// {
	// 	write(1, "", 0);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	g_signal = SIGQUIT;
	// }
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
