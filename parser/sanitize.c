/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:53:12 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/18 01:06:16 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sanitize_pipe(t_parser *token, t_parser **head)
{
	if (!token->next || !token->prev || token == *head)
		return (error_near_pipe(), 1);
	if (token->next->type != CMD && token->next->type != ENVVAR)
		return (error_near_pipe(), 1);
	if (token->prev->type != CMD && token->prev->type != CMD_ARG
		&& token->prev->type != ENVVAR && token->prev->type != EXIT_STATUS
		&& token->prev->type != FILENAME && token->next->type != REDIR_INPUT
		&& token->prev->type != IS_DELIMITER && token->prev->type != ENVVAR
		&& token->prev->type != EXIT_STATUS)
		return (error_near_pipe(), 1);
	return (0);
}

int	sanitize(t_parser **head)
{
	t_parser	*temp;

	temp = *head;
	// while (temp)
	// {
	// 	print_error(temp);
	// 	if (temp->type == PIPE && sanitize_pipe(temp, head))
	// 		return (1);
	// 	if (temp->type == REDIR_INPUT && sanitize_redir_input(temp))
	// 		return (1);
	// 	if (temp->type == REDIR_OUTPUT && sanitize_redir_output(temp))
	// 		return (1);
	// 	if (temp->type == REDIR_OUTPUT_APP && sanitize_redir_output_app(temp))
	// 		return (1);
	// 	if (temp->type == DELIMITER && sanitize_delimiter(temp))
	// 		return (1);
	// 	temp = temp->next;
	// }
	return (0);
}
