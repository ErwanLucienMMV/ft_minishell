/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:19:35 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/06 19:13:17 by abarthes         ###   ########.fr       */
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

static int	is_space_token(char *s)
{
	if (!s)
		return (0);
	if (s[0] == ' ' && ft_strlen(s) == 1)
		return (1);
	return (0);
}

static t_parser	*skip_n_flags(t_parser *temp, int *is_n)
{
	while (temp && temp->s && ((temp->s[0] == '-'
				&& valid_argument_n(temp->s))
			|| is_space_token(temp->s)))
	{
		if (!is_space_token(temp->s))
			*is_n = 1;
		temp = temp->next;
	}
	return (temp);
}

static void	print_echo_args(t_parser *temp)
{
	while (temp && temp->type == CMD_ARG)
	{
		if (!is_space_token(temp->s))
			printf("%s", temp->s);
		temp = temp->next;
		if (temp && temp->type == CMD_ARG)
			printf(" ");
	}
}

int	buildin_echo(t_parser *cmd, t_program *program)
{
	t_parser	*temp;
	int			is_n;

	is_n = 0;
	program->last_exit_status = 0;
	if (!cmd->next)
		return (printf("\n"), 0);
	temp = skip_n_flags(cmd->next, &is_n);
	print_echo_args(temp);
	if (!is_n)
		printf("\n");
	return (0);
}
