/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:17:52 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/27 15:31:32 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	handle_redirections(t_program *program)
{
	if (program->saved_stdin == -1)
		program->saved_stdin = dup(STDIN_FILENO);
	if (program->saved_stdout == -1)
		program->saved_stdout = dup(STDOUT_FILENO);
	if (file_handler(program->parsed))
	{
		program->last_exit_status = 1;
		parser_clear(program->parsed);
		return (1);
	}
	if (!there_is_at_least_one_pipe(*program->parsed))
	{
		program->here_doc_tempfile = HERE_DOC_TMPFILE;
		if(doing_here_doc(program, HERE_DOC_TMPFILE))
		{
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
	if (!there_is_at_least_one_pipe(*(program->parsed)))
	{
		buildins(program->parsed, *program->envpath, program);
	}
	if (!((*program->parsed)->s[0] == ':'
			&& ft_strlen((*program->parsed)->s) == 1))
		execve_handler(program);
	rl_replace_line("", 0);
	rl_redisplay();
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
