/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_individual_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:40:59 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:38:39 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sanitize_redir_input(t_parser *token)
{
	if (!get_next_non_space(token))
		return (error_near_newline(), 1);
	if (get_next_non_space(token)->type
		!= FILENAME && get_next_non_space(token)->type
		!= ENVVAR && get_next_non_space(token)->type != EXIT_STATUS)
		return (error_near_char("<"), 1);
	return (0);
}

int	sanitize_redir_output(t_parser *token)
{
	if (!get_next_non_space(token))
		return (error_near_newline(), 1);
	if (get_next_non_space(token)->type
		!= FILENAME && get_next_non_space(token)->type
		!= ENVVAR && get_next_non_space(token)->type != EXIT_STATUS)
		return (error_near_char(">"), 1);
	return (0);
}

int	sanitize_redir_output_app(t_parser *token)
{
	if (!get_next_non_space(token))
		return (error_near_newline(), 1);
	if (get_next_non_space(token)->type
		!= FILENAME && get_next_non_space(token)->type
		!= ENVVAR && get_next_non_space(token)->type != EXIT_STATUS)
		return (error_near_char(">>"), 1);
	return (0);
}

int	sanitize_delimiter(t_parser *token)
{
	if (!get_next_non_space(token))
		return (error_near_newline(), 1);
	if (get_next_non_space(token)->type != IS_DELIMITER)
		return (error_near_char("<<"), 1);
	return (0);
}
