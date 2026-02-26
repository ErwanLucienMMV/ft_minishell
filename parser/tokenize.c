/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:53:10 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/26 17:59:34 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	its_delimiter(t_parser **head, char *s, int *i)
{
	if (new_parser(head, parser_node_new(DELIMITER, (s), 2)) == 0)
		return (0);
	*i += 2;
	return (1);
}

int	its_redirection_output(t_parser **head, char *s, int *i)
{
	int			x;
	t_parser	*new;

	if (s[1] == '>')
	{
		x = 2;
		new = parser_node_new(REDIR_OUTPUT_APP, (s), x);
	}
	else
	{
		x = 1;
		new = parser_node_new(REDIR_OUTPUT, (s), x);
	}
	if (new == 0)
		return (0);
	new_parser(head, new);
	*i += x;
	return (1);
}

int	its_redirection_input(t_parser **head, char *s, int *i)
{
	int		x;

	x = 1;
	if (new_parser(head, parser_node_new(REDIR_INPUT, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	check_special_char(t_parser **head, char *s, int *i)
{
	if (*s == ' ')
		return (1);
	else if (*s == '$' && *(s + 1) == '?')
		return (its_exit_status(head, s, i));
	else if (*s == '$' && *(s + 1) != '?')
		return (its_env_var(head, s, i));
	else if (*s == '"')
		return (its_d_quote(head, s, i));
	else if (*s == '\'')
		return (its_s_quote(head, s, i));
	else if (*s == '|')
		return (its_pipe(head, s, i));
	else if (*s == '>' || (*s == '>' && *(s + 1) == '>'))
		return (its_redirection_output(head, s, i));
	else if (*s == '<' && *(s + 1) != '<')
		return (its_redirection_input(head, s, i));
	else if (*s == '<' && *(s + 1) == '<')
		return (its_delimiter(head, s, i));
	else if (*s == ';' || *s == '\\' || *s == '&' || *s == '!')
		return (print_error_token(s));
	else
		return (its_command(head, s, i));
}

t_parser	*parsing(char *s)
{
	int			i;
	t_parser	*head;

	head = 0;
	i = 0;
	while (s[i])
	{
		if (check_special_char(&head, (s + i), &i) == 0)
		{
			parser_clear(&head);
			return (NULL);
		}
		if (s[i] == ' ')
		{
			if (new_parser(&head, parser_node_new(T_SPACE, " ", 1)) == 0)
				return (parser_clear(&head), NULL);
			i++;
			continue ;
		}
	}
	return (head);
}
