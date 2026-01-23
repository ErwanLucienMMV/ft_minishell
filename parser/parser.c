/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:53:10 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/23 17:41:46 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int parser_clear(t_parser **lst)
{
	t_parser	*temp;
	t_parser	*next;

	if (!lst || !*lst)
		return (0);
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		free(temp->s);
		free(temp);
		temp = next;
	}
	*lst = 0;
	return (0);
}

t_parser	*get_last_parser(t_parser *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	parser_add_back(t_parser **lst, t_parser *new)
{
	t_parser	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_parser	*parser_node_new(lexer type, char *s, int x)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->type = type;
	new->s = malloc((x + 1) * sizeof(char));
	ft_strlcpy(new->s, s, x + 1);
	new->prev = 0;
	new->next = 0;
	return (new);
}

int	new_parser(t_parser **head, t_parser *new_node)
{
	if (!new_node)
		return (0);
	parser_add_back(head, new_node);
	return (1);
}

int	its_env_var(t_parser **head, char *s, int *i)
{
	int x;

	x = 0;
	while (s[x] && s[x] != ' ' && s[x] != '\t')	
		x++;
	if (new_parser(head, parser_node_new(ENVVAR, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	its_d_quote(t_parser **head, char *s, int *i)
{
	int x;

	x = 1;
	while (s[x] && s[x] != '"')	
		x++;
	x++;
	if (new_parser(head, parser_node_new(DQUOTE, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	its_s_quote(t_parser **head, char *s, int *i)
{
	int x;

	x = 1;
	while (s[x] && s[x] != '\'')	
		x++;
	x++;
	if (new_parser(head, parser_node_new(SQUOTE, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	its_exit_status(t_parser **head, char *s, int *i)
{
	if (new_parser(head, parser_node_new(EXIT_STATUS, (s), 2)) == 0)
		return (0);
	*i += 2;
	return (1);
}

int its_pipe(t_parser **head, char *s, int *i)
{
	if (new_parser(head, parser_node_new(PIPE, (s), 1)) == 0)
		return (0);
	*i += 1;
	return (1);
}

int	its_command(t_parser **head, char *s, int *i)
{
	int x;
	t_parser *new;

	x = 0;
	while (s[x] && s[x] != ' ' && s[x] != '\t' && s[x] != '|' && s[x] != '<'
		&& s[x] != '>' && s[x] != '\'' && s[x] != '"' && s[x] != '$' && s[x] != '?')	
		x++;
	if (get_last_parser(*head) && (get_last_parser(*head)->type == CMD
			|| get_last_parser(*head)->type == CMD_ARG))
		new = parser_node_new(CMD_ARG, (s), x);
	else if (get_last_parser(*head) && (get_last_parser(*head)->type == REDIR_OUTPUT
			|| get_last_parser(*head)->type == REDIR_OUTPUT_APP))
		new = parser_node_new(FILENAME, (s), x);
	else
		new = parser_node_new(CMD, (s), x);
	if (new == 0)
		return (0);
	new_parser(head, new);
	*i += x;
	return (1);
}

int its_redirection_output(t_parser **head, char *s, int *i)
{
	int x;
	t_parser *new;

	if (get_last_parser(*head)->type == REDIR_OUTPUT_APP)
		return (0);
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
	int x;

	x = 1;
	if (new_parser(head, parser_node_new(REDIR_INPUT, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	its_delimeter(t_parser **head, char *s, int *i)
{
	int x;

	x = 2;
	if (new_parser(head, parser_node_new(DELIMITER, (s), x)) == 0)
		return (0);
	*i += x;
	return (1);
}

int	check_special_char(t_parser **head, char *s, int *i)
{
	if (*s == '$' && *(s + 1) == '?')
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
		return (its_delimeter(head, s, i));
	else
		return (its_command(head, s, i));
}

t_parser	*parsing(char *s)
{
	int	i;
	t_parser *head;

	head = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			i++;
			continue;
		}
		if (check_special_char(&head, (s + i), &i) == 0)
		{
			parser_clear(&head);
			return (0);
		}
	}
	return (head);
}


// int main(void)
// {
// 	t_parser *test = parsing("pwd | \"ls -l\" >>file1");
// 	char *str;
// 	if (!test)
// 	{
// 		printf("syntax error\n");
// 		return (1);
// 	}
// 	while (test)
// 	{
// 		if (test->type == CMD)
// 			str = "CMD";
// 		else if (test->type == REDIR_OUTPUT)
// 			str = "REDIR_OUTPUT";
// 		else if (test->type == FILENAME)
// 			str = "FILENAME";
// 		else if (test->type == CMD_ARG)
// 			str = "CMD_ARG";
// 		else if (test->type == ENVVAR)
// 			str = "ENVVAR";
// 		else if (test->type == SQUOTE)
// 			str = "SQUOTE";
// 		else if (test->type == DQUOTE)
// 			str = "DQUOTE";
// 		else if (test->type == PIPE)
// 			str = "PIPE";
// 		else if (test->type == EXIT_STATUS)
// 			str = "EXIT_STATUS";
// 		else if (test->type == REDIR_INPUT)
// 			str = "REDIR_INPUT";
// 		else if (test->type == DELIMITER)
// 			str = "DELIMITER";
// 		else if (test->type == REDIR_OUTPUT_APP)
// 			str = "REDIR_OUTPUT_APP";
// 		else
// 			str = "OTHER ?????";
// 		printf("Type: %s | Str: %s\n", str, test->s);
// 		test = test->next;
// 	}
// 	return (10);
// }
