/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:10:31 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/10 18:13:11 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	free_envpath(t_envpath *envpath)
{
	t_envpath	*next;

	next = NULL;
	if (envpath && envpath->next)
		next = envpath->next;
	if (envpath && envpath->index)
	{
		free(envpath->index);
		envpath->index = NULL;
	}
	if (envpath && envpath->value)
	{
		free(envpath->value);
		envpath->value = NULL;
	}
	if (envpath)
	{
		free(envpath);
		envpath = NULL;
	}
	if (next)
		free_envpath(next);
}

void	free_parsers(t_parser *parser)
{
	t_parser	*next;

	next = NULL;
	if (parser && parser->next)
		next = parser->next;
	if (parser && parser->s)
	{
		free(parser->s);
		parser->s = NULL;
	}
	if (parser)
	{
		free(parser);
		parser = NULL;
	}
	if (next)
		free_parsers(next);
}

int	is_numeric_string(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_exit_arguments(t_program *p)
{
	t_parser	*first_arg;
	long		exit_status;

	if (!p->parsed || !*(p->parsed) || !(*p->parsed)->next)
		return (0);
	first_arg = (*p->parsed)->next;
	if (!parse_exit_status(first_arg->s, &exit_status))
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n", first_arg->s);
		p->last_exit_status = 2;
		return (0);
	}
	if (first_arg->next)
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		p->last_exit_status = 1;
		return (-1);
	}
	p->last_exit_status = (unsigned char)exit_status;
	return (0);
}

int	buildin_exit(t_program *program)
{
	int	exit_status;

	if (!program)
		exit(1);
	if (check_for_exit_arguments(program) == -1)
		return (1);
	write(1, "exit\n", 5);
	ft_exit(program);
	exit_status = program->last_exit_status;
	if (program->parsed)
	{
		free_parsers(*(program->parsed));
		free(program->parsed);
	}
	if (program->envpath)
	{
		free_envpath(*(program->envpath));
		free(program->envpath);
	}
	free(program);
	exit(exit_status);
	return (0);
}
