/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:03:53 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/30 17:40:16 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
// Avoid using readline internals here to stay portable across macOS libedit
#include <unistd.h>

extern volatile sig_atomic_t g_signal;

void sigint_handler(int signal)
{
	(void)signal;
	g_signal = SIGINT;
	write(1, "\n", 1);
}

void	set_signal_action(void)
{
	struct sigaction	act;
	// Met à 0 tous les bits dans la structure,
	// sinon on aura de mauvaises surprises de valeurs
	// non-initialisées...
 	ft_bzero(&act, sizeof(act));
	// On voudrait invoquer la routine sigint_handler
	// quand on reçoit le signal :
 	act.sa_handler = &sigint_handler;
	// Applique cette structure avec la fonction à invoquer
	// au signal SIGINT (ctrl-c)
 	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, NULL, NULL);
	sigaction(SIGTSTP, NULL, NULL);
}