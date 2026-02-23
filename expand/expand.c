/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:27 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 16:23:08 by abarthes         ###   ########.fr       */
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

//Check if there is an expansion to be done, and if so does it
//returns 1 on an expansion, and 0 if none were to be done
int	expand_specifics(t_envpath *envpath, t_program *program, t_parser *temp)
{
	if (temp && temp->type == ENVVAR && expand_env_var(&temp, envpath, program))
		return (1);
	else if (temp && temp->type == DQUOTE && expand_d_quote(&temp, envpath))
		return (1);
	else if (temp && temp->type == SQUOTE && expand_s_quote(&temp, program))
		return (1);
	else if (temp && temp->type == EXIT_STATUS
		&& expand_exit_status(temp, program->last_exit_status))
		return (1);
	else if (temp && (temp->type == CMD
			|| temp->type == CMD_ARG) && expand_plain_text(temp, envpath))
		return (1);
	return (0);
}

int	send_to_expand(t_envpath *envpath, t_program *program)
{
	t_parser	*temp;
	t_parser	*next;
	t_parser	*head_before;

	temp = *program->parsed;
	while (temp)
	{
		if (temp->type == T_SPACE)
		{
			temp = temp->next;
			continue ;
		}
		next = temp->next;
		head_before = *program->parsed;
		if (expand_specifics(envpath, program, temp) == 1)
			return (1);
		if (temp == head_before && *program->parsed != head_before)
			temp = *program->parsed;
		else
			temp = next;
	}
	return (0);
}
