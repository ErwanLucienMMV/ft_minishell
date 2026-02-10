/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:10:31 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/10 11:05:58 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

//SEGFAULT for a reason I cannot understand
void	free_envpath(t_envpath *envpath)
{
	t_envpath	*next;

	next = NULL;
	if (!envpath)
		return ;
	if (envpath->next)
		next = envpath->next;
	if (envpath->index)
		free(envpath->index);
	if (envpath->value)
	{
		free(envpath->value);
	}
	free(envpath);
	free_envpath(next);
}

void	free_parsers(t_parser *parser)
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
	free_parsers(next);
}

int	buildin_exit(t_program *program)
{
	int	exit_status;

	clear_history();
	if (!program)
		exit(1);
	unlink(program->here_doc_tempfile);
	exit_status = program->last_exit_status;
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
	exit(exit_status);
	return (0);
}
