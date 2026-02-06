/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:10:31 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/04 05:56:53 by emaigne          ###   ########.fr       */
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
	write(1, "handle the next node\n", 22);
	if (envpath->index)
		free(envpath->next);
	write(1, "freed the index\n", 17);
	if (envpath->value)
	{
		write(1, "value detected\n", 16);
		free(envpath->value);
		write(1, "freeing value\n", 15);
		/*segfault here on the second node*/
	}
	write(1, "freed the value\n", 17);
	write(1, "freeing the full NODE\n", 23);
	free(envpath);
	write(1, "test segfault\n", 15);
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
	clear_history();
	unlink(program->here_doc_tempfile);
	//does not work because somewhere the here_doc_tempfile is still open
	if (!program)
		exit(1);
	if (program->parsed)
	{
		free_parsers(*(program->parsed));
		free(program->parsed);
	}
//	SEGFAULT FOR A REASON I CANNOT UNDERSTAND, check with aurelien if the envpath is NULL terminated
	// if (program->envpath)
	// {
	// 	write(1, "freeing the envpath nodes now\n", 31);
	// 	free_envpath(*(program->envpath));
	// 	write(1, "freeing the envpath main now\n", 30);
	// 	free(program->envpath);
	// }
	write(1, "freeing the main structure now\n", 32);
	free(program);
	exit(0);
	return (0);
}
