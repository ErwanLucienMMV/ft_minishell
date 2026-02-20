/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_our_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:08:21 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:29:24 by emaigne          ###   ########.fr       */
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
	clearmatrix(splited_cmd);
	if (splited_cmd)
		free(splited_cmd);
}

void	clean_exit(char **splited_cmd, char *new_cmd)
{
	if (splited_cmd)
		free_splited_cmd(splited_cmd);
	if (new_cmd)
		free(new_cmd);
	exit(127);
}
