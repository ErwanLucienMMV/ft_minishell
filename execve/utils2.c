/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:45:14 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/10 18:59:33 by abarthes         ###   ########.fr       */
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

int	get_last_pid_and_return(t_program *p, t_commands *cmd, t_commands *first)
{
	int	lpid;

	lpid = last_exec(p, cmd, first);
	if (p->saved_stdin >= 0)
		dup2(p->saved_stdin, STDIN_FILENO);
	free_t_commands_and_args(first);
	return (lpid);
}

t_parser	*find_cmd_start_in_segment(t_parser *segment_start,
		t_parser *segment_end)
{
	t_parser	*temp;
	t_parser	*fallback;

	temp = segment_start;
	fallback = NULL;
	while (temp && temp != segment_end)
	{
		if (!fallback && (temp->type == REDIR_INPUT
				|| temp->type == REDIR_OUTPUT
				|| temp->type == REDIR_OUTPUT_APP
				|| temp->type == DELIMITER))
			fallback = temp;
		if (temp->type == CMD || temp->type == DELIMITER)
			return (temp);
		temp = temp->next;
	}
	return (fallback);
}
