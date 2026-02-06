/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:50:18 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/04 05:57:23 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

char	*find_path_line(char **env)
{
	char	*searched;
	int		i;
	int		j;

	searched = "PATH=";
	i = 0;
	while (env && env[i])
	{
		j = 0;
		while (env[i][j] && searched[j])
		{
			if (env[i][j] != searched[j])
				break ;
			j++;
		}
		if (searched[j] == '\0')
			return (env[i] + j);
		i++;
	}
	return (NULL);
}

char	*test_all_paths(char *command, char *pathline)
{
	char	*pathtested;
	char	**possiblepaths;
	int		i;

	i = 0;
	if (pathline == NULL)
		return (NULL);
	if (access(command, X_OK) == 0)
		return (command);
	possiblepaths = ft_split(pathline, ':');
	while (possiblepaths && possiblepaths[i])
	{
		pathtested = ft_strjoin(possiblepaths[i], command);
		if (pathtested && access(pathtested, X_OK) == 0)
			return (clearmatrix(possiblepaths), pathtested);
		free(pathtested);
		i++;
	}
	clearmatrix(possiblepaths);
	perror(command);
	return (NULL);
}

char	*find_command(char *command, char *pathline)
{
	char	*findaway;
	char	*pathcommand;

	if (command == NULL)
	{
		if (!(access(command, F_OK) == 0))
			perror("Permission denied");
		return (NULL);
	}
	if (access(command, X_OK) == 0)
	{
		return (command);
	}
	pathcommand = ft_strjoin("/", command);
	if (!pathcommand)
		return (NULL);
	findaway = test_all_paths(pathcommand, pathline);
	free(pathcommand);
	return (findaway);
}
