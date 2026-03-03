/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:22:21 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/03 16:23:13 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	*free_incomplete_matrix(char **tab, int lines)
{
	while (lines > 0)
		free(tab[lines--]);
	free(tab);
	return (NULL);
}

int	parse_count_cmd_args(t_parser *cmd)
{
	int		i;

	i = 0;
	while (cmd && (cmd->type == CMD || cmd->type == CMD_ARG))
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	get_heredoc_mod(t_parser *temp, int *mode)
{
	if (ft_strchr(temp->next->s, '"') || ft_strchr(temp->next->s, '\''))
		*mode = 0;
	if (ft_strchr(temp->next->s, '"'))
	{
		if (!search_and_replace(temp->next, '"'))
			return (1);
	}
	if (ft_strchr(temp->next->s, '\''))
	{
		if (!search_and_replace(temp->next, '\''))
			return (1);
	}
	return (0);
}
