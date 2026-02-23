/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:45:14 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 18:23:49 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

char	**ft_dup_matrix(char **tab)
{
	char	**dup;
	int		i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
		{
			while (i > 0)
				free(dup[--i]);
			free(dup);
			return (NULL);
		}
	}
	dup[i] = NULL;
	return (dup);
}

char	**provision_commands(t_parser *temp, char **splited_cmd)
{
	int		i;

	i = 1;
	splited_cmd[0] = ft_strdup(temp->s);
	if (!splited_cmd[0])
	{
		free_incomplete_matrix(splited_cmd, 0);
		return (NULL);
	}
	temp = temp->next;
	while (temp && temp->type == CMD_ARG)
	{
		splited_cmd[i++] = ft_strdup(temp->s);
		if (!splited_cmd[i - 1])
		{
			free_incomplete_matrix(splited_cmd, i - 1);
			return (NULL);
		}
		temp = temp->next;
	}
	splited_cmd[i] = NULL;
	return (splited_cmd);
}
