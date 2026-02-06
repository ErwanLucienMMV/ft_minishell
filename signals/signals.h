/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:01:59 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/06 12:30:09 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# if defined(__APPLE__)
/* Provide minimal prototypes when system headers don't declare them */
void rl_replace_line(const char *text, int clear_undo);
int rl_on_new_line(void);
void rl_redisplay(void);
# endif

void	set_signal_action(void);

#endif