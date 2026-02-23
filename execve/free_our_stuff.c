/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_our_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:08:21 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 12:31:32 by abarthes         ###   ########.fr       */
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
	tab = NULL;
}

void	free_splited_cmd(char **splited_cmd)
{
	clearmatrix(splited_cmd);
}

void	clean_exit(t_program *program, char **splited_cmd, char *new_cmd, int exit_code)
{
	if (splited_cmd)
		free_splited_cmd(splited_cmd);
	if (new_cmd)
		free(new_cmd);
	close(program->saved_stdin);
	close(program->saved_stdout);
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
	exit(exit_code);
}
