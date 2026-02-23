/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:01:59 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 16:56:34 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_signal_handlers
{
	struct sigaction	old_int;
	struct sigaction	old_quit;
	struct sigaction	old_tstp;
}	t_signal_handlers;

void				set_signal_action(void);
t_signal_handlers	setup_signals_before_fork(void);
void				setup_signals_after_fork(void);
void				restore_signals(t_signal_handlers handlers);

#endif