/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:15:20 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 14:33:51 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	free_t_command(t_commands *tofree)
{
	if (!tofree)
		return ;
	if (tofree->cmd)
		free_t_parser(tofree->cmd);
	if (tofree->args)
		clearmatrix(tofree->args);
	if (tofree->infile)
		free(tofree->infile);
	if (tofree->outfile)
		free(tofree->outfile);
	free(tofree);
}

void	free_t_program(t_program *program)
{
	unlink(program->here_doc_tempfile);
	if (program->parsed)
	{
		free_parsers(*(program->parsed));
		free(program->parsed);
		program->parsed = NULL;
	}
	if (program->envpath)
	{
		free_envpath(*(program->envpath));
		free(program->envpath);
		program->envpath = NULL;
	}
	free(program);
	program = NULL;
}

void	free_t_parser(t_parser *parser)
{
	t_parser	*next;

	next = NULL;
	if (!parser)
		return ;
	if (parser->next)
		next = parser->next;
	if (parser->s)
	{
		free(parser->s);
		parser->s = NULL;
	}
	free(parser);
	parser = NULL;
	free_t_parser(next);
}

void	free_t_cmd_prgrm_exit(t_commands *cmd, t_program *program)
{
	if (IS_DEBUG)
	{
		ft_printf_fd(2, "an issue while setting %s",
			"the pipes append and we exited\n");
	}
	free_t_command(cmd);
	free_t_program(program);
	exit(1);
}

//free ONLY the structure and the args inside, leaving the rest unattended
void	free_t_commands_and_args(t_commands *elem)
{
	t_commands	*next;

	next = elem->next;
	while (elem)
	{
		clearmatrix(elem->args);
		elem->args = NULL;
		free(elem);
		elem = NULL;
		elem = next;
		if (elem && elem->next)
			next = elem->next;
		else
			break ;
	}
}
