/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_exit_piped.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:16:32 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/26 14:54:53 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

int	check_for_exit_arguments_piped(t_program *p, t_commands *cmd)
{
	t_parser	*current;

	if (!p->parsed || !cmd->cmd || !cmd->cmd->next
		|| cmd->cmd->next->type != CMD_ARG)
		return (0);
	current = cmd->cmd->next;
	if (!is_numeric_string(current->s) || !ft_strtol(current->s))
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n", current->s);
		p->last_exit_status = 255;
		return (0);
	}
	p->last_exit_status = ft_strtol(current->s) % 256;
	return (0);
}

int	exit_piped(t_program *program, t_commands *cmd, t_commands *first)
{
	int	exit_status;

	if (!program)
		exit(1);
	check_for_exit_arguments_piped(program, cmd);
	free_t_commands_and_args(first);
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
