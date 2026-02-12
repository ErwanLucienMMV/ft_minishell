/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:01:03 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/12 16:22:29 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	error_message_file_not_found(char *filename)
{
	char	*src;

	src = malloc(ft_strlen("miniswag: ") + ft_strlen(filename) + 1);
	if (!src)
		return ;
	ft_strlcpy(src, "miniswag: ", ft_strlen("miniswag: ") + 1);
	ft_strlcat(src, filename, ft_strlen("miniswag: ") + ft_strlen(filename) + 1);
	perror(src);
	free(src);
}

void	error_near_newline()
{
	ft_printf_fd(2, "miniswag: syntax error near unexpected token `newline'\n");
}

void	error_message_command_not_found(char *command)
{
	ft_printf_fd(2, "miniswag: %s: command not found\n", command);
}

void	error_near_pipe()
{
	ft_printf_fd(2, "miniswag: syntax error near unexpected token `|'\n");
}

void	error_near_char(char *str)
{
	ft_printf_fd(2, "miniswag: syntax error near unexpected token `%s'\n", str);
}