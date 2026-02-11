/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:01:03 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/11 13:21:39 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	error_message_file_not_found(char *filename)
{
	char	*src;

	src = malloc(ft_strlen("minishell: ") + ft_strlen(filename) + 1);
	if (!src)
		return ;
	ft_strlcpy(src, "minishell: ", ft_strlen("minishell: ") + 1);
	ft_strlcat(src, filename, ft_strlen("minishell: ") + ft_strlen(filename) + 1);
	perror(src);
	free(src);
}

void	error_near_newline()
{
	ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
}

void	error_message_command_not_found(char *command)
{
	ft_printf_fd(2, "miniswag: %s: command not found\n", command);
}