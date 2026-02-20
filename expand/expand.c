/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:27 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 08:08:14 by emaigne          ###   ########.fr       */
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

	temp = *program->parsed;
	while (temp)
	{
		if (temp->type == T_SPACE)
		{
			temp = temp->next;
			continue ;
		}
		if (expand_specifics(envpath, program, temp) == 1)
			return (1);
		if (temp)
			temp = temp->next;
		else if (*(program->parsed))
		{
			temp = *(program->parsed);
		}
		else
			temp = 0;
	}
	return (0);
}
