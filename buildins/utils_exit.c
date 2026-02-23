/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:47:56 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 16:55:37 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	ft_exit(t_program *program)
{
	clear_history();
	if (program->here_doc_tempfile)
		unlink(program->here_doc_tempfile);
	if (program->saved_stdin != -1)
		close (program->saved_stdin);
	if (program->saved_stdout != -1)
		close (program->saved_stdout);
}
