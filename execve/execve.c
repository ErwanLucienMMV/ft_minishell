/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:44:15 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 08:27:08 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include "../signals/signals.h"

int	execve_handler(t_program *program)
{
	int	status;
	int	last_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (there_is_at_least_one_pipe(*(program->parsed)))
	{
		if (execve_with_pipe(program))
			return (1);
	}
	else
	{
		if (execve_without_pipe(program, program->parsed,
				*(program->envpath), program->envp))
			return (1);
	}
	last_status = 0;
	set_signal_action();
	while (waitpid(-1, &status, 0) > 0)
		last_status = WEXITSTATUS(status);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	program->last_exit_status = last_status;
	return (last_status);
}
