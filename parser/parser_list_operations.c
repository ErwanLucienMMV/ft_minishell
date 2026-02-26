/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:34:15 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/26 17:55:09 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_clear(t_parser **lst)
{
	t_parser	*temp;
	t_parser	*next;

	if (!lst || !*lst)
		return (0);
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		if (temp->s)
		{
			free(temp->s);
			temp->s = NULL;
		}
		free(temp);
		temp = NULL;
		temp = next;
	}
	*lst = 0;
	return (0);
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
		new->prev = temp;
	}
}

t_parser	*parser_node_new(t_lexer type, char *s, int x)
{
	t_parser	*new;

	new = ft_calloc(1, sizeof(t_parser));
	if (!new)
		return (NULL);
	new->type = type;
	new->s = ft_calloc((x + 1), sizeof(char));
	if (!new->s)
		return (free(new), NULL);
	ft_strlcpy(new->s, s, x + 1);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	its_env_var(t_parser **head, char *s, int *i)
{
	int		x;

	x = 1;
	while (s[x] && (ft_isalnum(s[x]) || s[x] == '_')
		&& s[x] != '"' && s[x] != ' ')
		x++;
	if (get_prev_non_space(get_last_parser(*head))
		&& get_prev_non_space(get_last_parser(*head))->type == DELIMITER)
	{
		if (new_parser(head, parser_node_new(IS_DELIMITER, (s), x)) == 0)
			return (0);
		*i += x;
		return (1);
	}
	if (x == 1)
		return (its_command(head, s, i));
	if (new_parser(head, parser_node_new(ENVVAR,
				s + 1, x - 1)) == 0)
		return (0);
	*i += x;
	return (1);
}
