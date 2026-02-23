/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:10:31 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/23 14:04:33 by abarthes         ###   ########.fr       */
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
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_exit_arguments(t_program *program)
{
	t_parser	*current;

	if (!program->parsed || !*(program->parsed) || !(*program->parsed)->next)
		return (0);
	current = (*program->parsed)->next;
	while (current)
	{
		if (!is_numeric_string(current->s) || !ft_strtol(current->s))
		{
			ft_printf_fd(2, "exit: %s: numeric argument required\n", current->s);
			program->last_exit_status = 255;
			return (0);
		}
		current = current->next;
	}
	if (program->parsed && *(program->parsed)
		&& (*program->parsed)->next && (*program->parsed)->next->next)
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		return (1);
	}
	if (program->parsed && *(program->parsed) && (*program->parsed)->next)
		return (ft_strtol((*program->parsed)->next->s) % 256);
	return (0);
}

int	buildin_exit(t_program *program)
{
	int	exit_status;

	clear_history();
	if (!program)
		exit(1);
	ft_printf_fd(2, "exit\n");
	exit_status = check_for_exit_arguments(program);
	unlink(program->here_doc_tempfile);
	if (exit_status == 0)
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
