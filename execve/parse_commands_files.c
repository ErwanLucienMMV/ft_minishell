/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:22:16 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 06:30:43 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

/*** 
 *	Find a name not currently used to create a new fd
 * 	By concatenating a character with ".heredoc_temp_file"
 * 	return said name after testing it does not exist yet so no data is lost
 * ***/
char	*get_a_valid_name(void)
{
	char	*filename;
	char	*totry;
	char	*it;

	totry = ft_strdup(".heredoc_temp_file");
	if (totry == NULL)
		return (NULL);
	it = ft_strdup("0");
	if (it == NULL)
		return (free(totry), NULL);
	while (1)
	{
		it[0] += 1;
		filename = ft_strjoin(totry, it);
		if (!filename)
			return (free(totry), free(it), NULL);
		if (access(filename, F_OK) == -1)
			return (free(totry), free(it), filename);
		free(filename);
		filename = NULL;
	}
	return (NULL);
}

static int	handle_input_redir(t_parser *temp, t_commands *tofill)
{
	free(tofill->infile);
	tofill->infile = ft_strdup(temp->next->s);
	if (!tofill->infile)
		return (1);
	if (access(tofill->infile, F_OK | R_OK) != 0)
		return (1);
	return (0);
}

static int	handle_here_doc(t_parser **temp, t_commands *tofill)
{
	free(tofill->infile);
	tofill->infile = get_a_valid_name();
	if (!tofill->infile)
		return (1);
	doing_here_doc_util(*temp, tofill->infile);
	*temp = (*temp)->next;
	return (0);
}

static int	handle_output_redir(t_parser *temp, t_commands *tofill)
{
	free(tofill->outfile);
	tofill->outfile = ft_strdup(temp->next->s);
	if (!tofill->outfile)
		return (1);
	tofill->redir_type = temp->type;
	return (0);
}

int	check_for_redirections(t_parser *cmd, t_commands *tofill)
{
	t_parser	*temp;

	temp = cmd;
	while (temp && temp->prev && temp->prev->type != PIPE)
		temp = temp->prev;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIR_INPUT && temp->next)
			if (handle_input_redir(temp, tofill))
				return (1);
		if (temp->type == DELIMITER && temp->next)
			if (handle_here_doc(&temp, tofill))
				return (1);
		if ((temp->type == REDIR_OUTPUT
				|| temp->type == REDIR_OUTPUT_APP) && temp->next)
			if (handle_output_redir(temp, tofill))
				return (1);
		temp = temp->next;
	}
	return (0);
}
