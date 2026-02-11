/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:27 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/11 13:55:31 by abarthes         ###   ########.fr       */
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
	char	*value;

	if (ft_strlen(node->s) == 0)
	{
		free(node->s);
		node->s = ft_strdup("$");
		if (node->prev && (node->prev->type == CMD
				|| node->prev->type == CMD_ARG))
			node->type = CMD_ARG;
		else
			node->type = CMD;
		return (0);
	}
	value = get_env_value_by_key(&envpath, node->s);
	if (value)
	{
		free(node->s);
		node->s = ft_strdup(value);
		if (node->prev && (node->prev->type == CMD
				|| node->prev->type == CMD_ARG))
			node->type = CMD_ARG;
		else
			node->type = CMD;
	}
	else
	{
		free(node->s);
		node->s = ft_strdup("");
		if (node->prev && (node->prev->type == CMD
				|| node->prev->type == CMD_ARG))
			node->type = CMD_ARG;
		else
			node->type = CMD;
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
	if (node->prev && node->prev->type == CMD)
		node->type = CMD_ARG;
	else
		node->type = CMD;
	return (0);
}

int	send_to_expand(t_parser **parsed, t_envpath *envpath, t_program *program)
{
	t_parser	*temp;

	temp = *parsed;
	while (temp)
	{
		if (temp->type == ENVVAR)
			expand_env_var(temp, envpath);
		else if (temp->type == DQUOTE)
			expand_d_quote(temp, envpath);
		else if (temp->type == SQUOTE)
			expand_s_quote(temp);
		else if (temp->type == EXIT_STATUS)
			expand_exit_status(temp, program->last_exit_status);
		else if (temp->type == CMD || temp->type == CMD_ARG)
			expand_plain_text(temp, envpath);
		temp = temp->next;
	}
	return (0);
}
