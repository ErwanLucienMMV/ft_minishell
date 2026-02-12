/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:53:12 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/12 19:43:25 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// void print_error(t_parser *temp)
// {
// 	printf("sanitizing..\n");
// 	char	*str;

// 	while (temp)
// 	{
// 		if (temp->type == CMD)
// 			str = "CMD";
// 		else if (temp->type == REDIR_OUTPUT)
// 			str = "REDIR_OUTPUT";
// 		else if (temp->type == FILENAME)
// 			str = "FILENAME";
// 		else if (temp->type == CMD_ARG)
// 			str = "CMD_ARG";
// 		else if (temp->type == ENVVAR)
// 			str = "ENVVAR";
// 		else if (temp->type == SQUOTE)
// 			str = "SQUOTE";
// 		else if (temp->type == DQUOTE)
// 			str = "DQUOTE";
// 		else if (temp->type == PIPE)
// 			str = "PIPE";
// 		else if (temp->type == EXIT_STATUS)
// 			str = "EXIT_STATUS";
// 		else if (temp->type == REDIR_INPUT)
// 			str = "REDIR_INPUT";
// 		else if (temp->type == REDIR_OUTPUT_APP)
// 			str = "REDIR_OUTPUT_APP";
// 		else if (temp->type == DELIMITER)
// 			str = "DELIMITER";
// 		else if (temp->type == IS_DELIMITER)
// 			str = "IS_DELIMITER";
// 		else
// 			str = "OTHER ?????";
// 		printf("Type: %s | Str: %s\n", str, temp->s);
// 		temp = temp->next;
// 	}
// }

int	sanitize_pipe(t_parser *token, t_parser **head)
{
	if (!token->next || !token->prev || token == *head)
		return (error_near_pipe(), 1);
	if (token->next->type != CMD)
		return (error_near_pipe(), 1);
	if (token->prev->type != CMD && token->prev->type != CMD_ARG
		&& token->prev->type != ENVVAR && token->prev->type != EXIT_STATUS
		&& token->prev->type != FILENAME && token->next->type != REDIR_INPUT)
		return (error_near_pipe(), 1);
	return (0);
}

int	sanitize_redir_input(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != FILENAME)
		return (error_near_char("<"), 1);
	return (0);
}

int	sanitize_redir_output(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != FILENAME)
		return (error_near_char(">"), 1);
	return (0);
}

int	sanitize_redir_output_app(t_parser *token)
{
	if (!token->next)
		return (error_near_newline(), 1);
	if (token->next->type != FILENAME)
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

int	sanitize(t_parser **head)
{
	t_parser	*temp;

	//print_error(*head);
	temp = *head;
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
