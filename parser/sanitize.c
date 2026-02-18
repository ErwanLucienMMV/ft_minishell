/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:53:12 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/18 16:30:55 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*get_next_non_space(t_parser *token)
{
	if (!token)
		return (NULL);
	token = token->next;
	while (token && token->type == T_SPACE)
		token = token->next;
	return (token);
}

t_parser	*get_prev_non_space(t_parser *token)
{
	if (!token)
		return (NULL);
	token = token->prev;
	while (token && token->type == T_SPACE)
		token = token->prev;
	return (token);
}

int	sanitize_pipe(t_parser *token, t_parser **head)
{
	if (!get_next_non_space(token)
		|| !get_prev_non_space(token)
		|| token == *head)
		return (error_near_pipe(), 1);
	if (get_next_non_space(token)->type != CMD
		&& get_next_non_space(token)->type != ENVVAR
		&& get_next_non_space(token)->type != REDIR_INPUT)
		return (error_near_pipe(), 1);
	if (get_prev_non_space(token)->type != CMD
		&& get_prev_non_space(token)->type != CMD_ARG
		&& get_prev_non_space(token)->type != ENVVAR
		&& get_prev_non_space(token)->type != EXIT_STATUS
		&& get_prev_non_space(token)->type != FILENAME
		&& get_prev_non_space(token)->type != IS_DELIMITER
		&& get_prev_non_space(token)->type != DQUOTE
		&& get_prev_non_space(token)->type != SQUOTE)
		return (error_near_pipe(), 1);
	return (0);
}

int	sanitize(t_parser **head)
{
	t_parser	*temp;

	temp = *head;
	// print_error(temp);
	while (temp)
	{
		if (temp->type == PIPE && sanitize_pipe(temp, head))
			return (1);
		if (temp->type == REDIR_INPUT && sanitize_redir_input(temp))
			return (1);
		if (temp->type == REDIR_OUTPUT && sanitize_redir_output(temp))
			return (1);
		if (temp->type == REDIR_OUTPUT_APP && sanitize_redir_output_app(temp))
			return (1);
		if (temp->type == DELIMITER && sanitize_delimiter(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}
