/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fhandler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:56:56 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/31 13:26:50 by abarthes         ###   ########.fr       */
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

int	make_redirection(t_parser **parsed)
{
	t_parser	*last_file_output;
	t_parser	*last_file_input;
	int			fd;

	last_file_output = get_last_output_file(parsed);
	last_file_input = get_last_input_file(parsed);

	if (last_file_output)
	{
		fd = open(last_file_output->s, O_WRONLY);
		if (fd < 0)
		{
			char src[1024] = "minishell: ";
			ft_strlcat(src, last_file_output->s, 1010);
			perror(src);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (last_file_input)
	{
		fd = open(last_file_input->s, O_RDONLY);
		if (fd < 0)
		{
			char src[1024] = "minishell: ";
			ft_strlcat(src, last_file_input->s, 1010);
			perror(src);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	create_files(t_parser **parsed)
{
	t_parser *temp;
	int		fd;

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
	t_parser *temp;
	int		fd;

	temp = *parsed;
	while (temp)
	{
		if (temp->type == REDIR_INPUT)
		{
			fd = open(temp->next->s, O_RDONLY);
			if (fd < 0)
			{
				char src[1024] = "minishell: ";
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
	if (make_redirection(parsed) != 0)
		return (1);
	return (0);
}