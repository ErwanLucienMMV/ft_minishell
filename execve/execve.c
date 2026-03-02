/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:44:15 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/27 17:52:45 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include "../signals/signals.h"
#include <signal.h>

int	execve_maker(t_program *program)
{
	t_signal_handlers	handlers;
	int					lpid;

	handlers = setup_signals_before_fork();
	if (there_is_at_least_one_pipe(*(program->parsed)))
	{
		lpid = execve_with_pipe(program);
		if (lpid == 0)
			return (restore_signals(handlers), 0);
		else
			return (restore_signals(handlers), lpid);
	}
	else
	{
		lpid = execve_without_pipe(program, program->parsed,
				*(program->envpath), program->envp);
		if (lpid == 0)
			return (restore_signals(handlers), 0);
		else
			return (restore_signals(handlers), lpid);
	}
	return (restore_signals(handlers), 1);
}

void	handle_piped_exec_exit(t_program *program, int pid)
{
	int	store_status;

	waitpid(pid, &store_status, 0);
	if (WIFEXITED(store_status))
		program->last_exit_status = WEXITSTATUS(store_status);
	else if (WIFSIGNALED(store_status))
	{
		if (WTERMSIG(store_status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else
			write(STDOUT_FILENO, "\n", 1);
		program->last_exit_status = 128 + WTERMSIG(store_status);
	}
}

int	wait_for_childrens(void)
{
	int	status;
	int	already_n;
	int	last_status;

	already_n = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status) && !already_n)
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			else
				write(STDOUT_FILENO, "\n", 1);
			already_n = 1;
		}
		last_status = WEXITSTATUS(status);
	}
	return (last_status);
}

int	execve_handler(t_program *program)
{
	int					last_status;
	t_signal_handlers	handlers;

	program->last_exit_status = 0;
	handlers = setup_signals_before_fork();
	last_status = execve_maker(program);
	if (last_status == 0)
		return (1);
	setup_signals_after_fork();
	if (last_status != 1)
		handle_piped_exec_exit(program, last_status);
	last_status = wait_for_childrens();
	restore_signals(handlers);
	tcsetattr(STDIN_FILENO, TCSANOW, &program->g_term_orig);
	if (program->last_exit_status == -1)
		program->last_exit_status = last_status;
	return (last_status);
}
