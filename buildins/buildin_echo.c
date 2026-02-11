/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:19:35 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/11 13:43:54 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	valid_argument_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	buildin_echo(t_parser *cmd, t_program *program)
{
	t_parser	*temp;
	int			is_n;

	is_n = 0;
	program->last_exit_status = 0;
	if (!cmd->next)
		return (printf("\n"), 0);
	temp = cmd->next;
	while (temp && temp->s && temp->s[0] == '-' && valid_argument_n(temp->s))
	{
		is_n = 1;
		temp = temp->next;
	}
	while (temp && (temp->type == CMD || temp->type == CMD_ARG))
	{
		printf("%s", temp->s);
		temp = temp->next;
		if (temp)
			printf(" ");
	}
	if (!is_n)
		printf("\n");
	return (0);
}
