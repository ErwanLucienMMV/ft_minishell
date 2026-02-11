/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:17:52 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/11 09:00:35 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	handle_redirections(t_program *program)
{
	program->saved_stdin = dup(STDIN_FILENO);
	program->saved_stdout = dup(STDOUT_FILENO);
	if (file_handler(program->parsed))
		return (1);
	program->here_doc_tempfile = HERE_DOC_TMPFILE;
	doing_here_doc(program->parsed);
	return (0);
}

void	handle_expansions(t_program *program)
{
	print_debug(program);
	send_to_expand(program->parsed, *program->envpath, program);
	print_debug(program);
}

void	execute_and_restore(t_program *program)
{
	if (!there_is_at_least_one_pipe(*(program->parsed)))
	{
		buildins(program->parsed, *program->envpath, program);
	}
	execve_handler(program);
	rl_replace_line("", 0);
	rl_redisplay();
	dup2(program->saved_stdin, STDIN_FILENO);
	dup2(program->saved_stdout, STDOUT_FILENO);
	close(program->saved_stdin);
	close(program->saved_stdout);
	parser_clear(program->parsed);
}
