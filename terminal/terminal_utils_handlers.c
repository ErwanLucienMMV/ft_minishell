/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:17:52 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/09 16:08:52 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	handle_redirections(t_program *program)
{
	int	has_pipe;

	has_pipe = there_is_at_least_one_pipe(*program->parsed);
	if (program->saved_stdin == -1)
		program->saved_stdin = dup(STDIN_FILENO);
	if (program->saved_stdout == -1)
		program->saved_stdout = dup(STDOUT_FILENO);
	if (!has_pipe)
	{
		program->here_doc_tempfile = HERE_DOC_TMPFILE;
		if (doing_here_doc(program, HERE_DOC_TMPFILE))
		{
			if (access(HERE_DOC_TMPFILE, F_OK) == 0)
				unlink(HERE_DOC_TMPFILE);
			if (program->last_exit_status != 130)
				program->last_exit_status = 1;
			parser_clear(program->parsed);
			return (1);
		}
	}
	return (0);
}

void	handle_expansions(t_program *program)
{
	print_debug(program);
	send_to_expand(*program->envpath, program);
	add_empty_nodes_to_their_next(program);
	remove_useless_space_nodes(program);
	restore_types_after_expansion(program->parsed);
	print_debug(program);
}

void	execute_and_restore(t_program *program)
{
	int	buildin_handled;

	buildin_handled = 0;
	if (!there_is_at_least_one_pipe(*(program->parsed)))
		buildin_handled = buildins(program->parsed, *program->envpath, program);
	if (!buildin_handled && !((*program->parsed)->s[0] == ':'
			&& ft_strlen((*program->parsed)->s) == 1))
		if (execve_handler(program) == 1)
			return ;
	if (program->saved_stdin >= 0)
	{
		dup2(program->saved_stdin, STDIN_FILENO);
		close(program->saved_stdin);
		program->saved_stdin = -1;
	}
	if (program->saved_stdout >= 0)
	{
		dup2(program->saved_stdout, STDOUT_FILENO);
		close(program->saved_stdout);
		program->saved_stdout = -1;
	}
	parser_clear(program->parsed);
}
