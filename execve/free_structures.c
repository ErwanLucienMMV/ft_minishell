/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:15:20 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:13:41 by emaigne          ###   ########.fr       */
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
	}
	if (program->envpath)
	{
		free_envpath(*(program->envpath));
		free(program->envpath);
	}
	free(program);
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
		free(parser->s);
	free(parser);
	free_t_parser(next);
}

void	free_t_cmd_prgrm_exit(t_commands *cmd, t_program *program)
{
	free_t_command(cmd);
	free_t_program(program);
	exit(1);
}
