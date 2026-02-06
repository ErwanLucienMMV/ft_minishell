/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:17:52 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/04 03:25:17 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	handle_redirections(t_program *program)
{
	program->saved_stdin = dup(STDIN_FILENO);
	program->saved_stdout = dup(STDOUT_FILENO);
	file_handler(program->parsed);
	program->here_doc_tempfile = ".here_doc_tempfile";
	doing_here_doc(program->parsed);
}

void	handle_expansions(t_program *program)
{
	print_debug(program);
	send_to_expand(program->parsed, *program->envpath, program);
	print_debug(program);
}

void	execute_and_restore(t_program *program)
{
	buildins(program->parsed, *program->envpath, program);
	execve_handler(program);
	rl_replace_line("", 0);
	rl_redisplay();
	dup2(program->saved_stdin, STDIN_FILENO);
	dup2(program->saved_stdout, STDOUT_FILENO);
	close(program->saved_stdin);
	close(program->saved_stdout);
	parser_clear(program->parsed);
}
