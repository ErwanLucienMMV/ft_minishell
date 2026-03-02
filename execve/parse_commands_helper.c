/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:22:21 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/02 14:49:33 by emaigne          ###   ########.fr       */
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

int	get_heredoc_mod(t_parser *temp)
{
	int		mode;
	char	*str;

	mode = 1;
	if (ft_strchr(temp->next->s, '"') || ft_strchr(temp->next->s, '\''))
		mode = 0;
	if (ft_strchr(temp->next->s, '"'))
	{
		str = ft_strtrim(temp->next->s, "\"");
		if (!str)
			return (perror("here_doc: strtrim"), 1);
		free(temp->next->s);
		temp->next->s = str;
	}
	if (ft_strchr(temp->next->s, '\''))
	{
		str = ft_strtrim(temp->next->s, "'");
		if (!str)
			return (perror("here_doc: strtrim"), 1);
		free(temp->next->s);
		temp->next->s = str;
	}
	return (mode);
}
