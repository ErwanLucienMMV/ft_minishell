/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:40:33 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/06 19:06:02 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	check_at_least_one_node(t_program *program)
{
	*(program->parsed) = get_first_parser(*(program->parsed));
	if (!*(program->parsed))
		return (1);
	return (0);
}

void	delete_redirections(t_program *program)
{
	t_parser	*temp;
	t_parser	*next;

	temp = *program->parsed;
	while (temp)
	{
		next = temp->next;
		if (temp->type == REDIR_INPUT || temp->type == REDIR_OUTPUT
			|| temp->type == REDIR_OUTPUT_APP || temp->type == FILENAME)
			parser_clear_one(&temp, program);
		temp = next;
	}
}
