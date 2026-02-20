/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_without_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:26:42 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:31:12 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"
#include "../here_doc/here_doc.h"
#include "../signals/signals.h"

t_parser	*get_first_cmd_no_buildins(t_parser *cmd)
{
	t_parser	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->type == CMD && !is_a_buildin(temp->s))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	exec_one_command(t_program *program,
	t_parser *cmd, char *path, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("pid"), exit(1));
	if (pid)
		return ;
	else
		do_command(program, cmd, path, envp);
}

int	execve_without_pipe(t_program *program,
	t_parser **parsed, t_envpath *envpath, char **envp)
{
	t_parser	*cmd;

	cmd = get_first_cmd_no_buildins(*parsed);
	if (!cmd)
		return (1);
	make_redirection(*parsed);
	exec_one_command(program, cmd,
		get_env_value_by_key(&envpath, "PATH"), envp);
	return (0);
}
