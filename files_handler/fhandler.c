/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fhandler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:56:56 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/04 05:56:14 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhandler.h"

t_parser	*get_last_output_file(t_parser **parsed)
{
	t_parser	*temp;
	t_parser	*file;

	temp = *parsed;
	file = 0;
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APP)
		{
			temp = temp->next;
			file = temp;
		}
		temp = temp->next;
	}
	return (file);
}

t_parser	*get_last_input_file(t_parser **parsed)
{
	t_parser	*temp;
	t_parser	*file;

	temp = *parsed;
	file = 0;
	while (temp)
	{
		if (temp->type == REDIR_INPUT)
		{
			temp = temp->next;
			file = temp;
		}
		temp = temp->next;
	}
	return (file);
}

int	create_files(t_parser **parsed)
{
	t_parser	*temp;
	int			fd;

	temp = *parsed;
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APP)
		{
			if (temp->type == REDIR_OUTPUT)
				fd = open(temp->next->s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(temp->next->s, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("Error creating output file");
				return (1);
			}
			close(fd);
		}
		temp = temp->next;
	}
	return (0);
}

int	check_exist_files(t_parser **parsed)
{
	t_parser	*temp;
	int			fd;
	char		src[1024];

	temp = *parsed;
	while (temp)
	{
		if (temp->type == REDIR_INPUT)
		{
			fd = open(temp->next->s, O_RDONLY);
			if (fd < 0)
			{
				ft_strlcat(src, "minishell: ", 1024);
				ft_strlcat(src, temp->next->s, 1010);
				perror(src);
				return (1);
			}
			close(fd);
		}
		temp = temp->next;
	}
	return (0);
}

int	file_handler(t_parser **parsed)
{
	if (check_exist_files(parsed) != 0)
		return (1);
	if (create_files(parsed) != 0)
		return (1);
	return (0);
}
