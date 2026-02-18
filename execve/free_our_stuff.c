/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_our_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:08:21 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/18 16:56:20 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	clearmatrix(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = 0;
		i++;
	}
	free(tab);
	tab = 0;
}

void	free_splited_cmd(char **splited_cmd)
{
	if (splited_cmd)
		free(splited_cmd);
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

void	clean_exit(char **splited_cmd, char *new_cmd)
{
	if (splited_cmd)
		free_splited_cmd(splited_cmd);
	if (new_cmd)
		free(new_cmd);
	exit(127);
}

