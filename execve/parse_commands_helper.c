/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:22:21 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 17:26:23 by emaigne          ###   ########.fr       */
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
