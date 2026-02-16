/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:27 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/16 12:59:43 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_exit_status(t_parser *node, int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (1);
	free(node->s);
	node->s = status_str;
	node->type = CMD_ARG;
	return (0);
}

int	expand_env_var(t_parser *node, t_envpath *envpath)
{
	char		*value;

	if (ft_strlen(node->s) == 0)
		return (set_node_type(node), 0);
	value = get_env_value_by_key(&envpath, node->s);
	if (value)
	{
		int there_is_echo = get_prev_echo(node) != NULL;
		t_parser	*expanded_one = parsing_after_expand(value, there_is_echo);
		t_parser	*expanded_next;
		t_parser	*next;
		t_parser	*prev;
		if (!expanded_one)
			return (1);
		expanded_next = expanded_one->next;
		prev = node->prev;
		next = node->next;
		free(node->s);
		node->type = expanded_one->type;
		node->s = expanded_one->s;
		node->prev = prev;
		node->next = expanded_next;
		if (expanded_next)
			expanded_next->prev = node;
		if (prev)
			prev->next = node;
		if (next)
		{
			t_parser	*tail = get_last_parser(node);
			next->prev = tail;
			tail->next = next;
		}
		free(expanded_one);
		t_parser	*cur;
		t_parser	*stop;

		cur = node;
		stop = next;
		while (cur && cur != stop)
		{
			set_node_type(cur);
			cur = cur->next;
		}
	}
	else
	{
		free(node->s);
		node->s = ft_strdup("");
		set_node_type(node);
	}
	return (0);
}

int	expand_s_quote(t_parser *node)
{
	char	*new_str;
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (1);
	ft_strlcpy(new_str, node->s + 1, len - 1);
	free(node->s);
	node->s = new_str;
	set_node_type(node);
	return (0);
}

int	send_to_expand(t_parser **parsed, t_envpath *envpath, t_program *program)
{
	t_parser	*temp;
	int	i;

	temp = *parsed;
	i = 0;
	while (temp)
	{
		if (temp && temp->type == ENVVAR && expand_env_var(temp, envpath))
			return (1);
		else if (temp && temp->type == DQUOTE && expand_d_quote(&temp, envpath))
			return (1);
		else if (temp && temp->type == SQUOTE && expand_s_quote(temp))
			return (1);
		else if (temp && temp->type == EXIT_STATUS && expand_exit_status(temp, program->last_exit_status))
			return (1);
		else if (temp && (temp->type == CMD || temp->type == CMD_ARG) && expand_plain_text(temp, envpath))
			return (1);
		if (!temp && i == 0)
		{
			*parsed = 0;
			return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}
