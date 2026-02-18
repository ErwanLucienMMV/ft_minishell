/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_individual_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:40:59 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/18 00:44:19 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sanitize_redir_input(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != FILENAME && token->next->type
		!= ENVVAR && token->next->type != EXIT_STATUS)
		return (error_near_char("<"), 1);
	return (0);
}

int	sanitize_redir_output(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != FILENAME && token->next->type
		!= ENVVAR && token->next->type != EXIT_STATUS)
		return (error_near_char(">"), 1);
	return (0);
}

int	sanitize_redir_output_app(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != FILENAME && token->next->type
		!= ENVVAR && token->next->type != EXIT_STATUS)
		return (error_near_char(">>"), 1);
	return (0);
}

int	sanitize_delimiter(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != IS_DELIMITER)
		return (error_near_char("<<"), 1);
	return (0);
}