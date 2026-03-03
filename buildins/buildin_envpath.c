/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_envpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:15:48 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/03 16:30:59 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	buildin_env(t_program *program)
{
	if (get_env_value_by_key(program->envpath, "PATH") == NULL)
	{
		write(STDERR_FILENO, "minishell: env: No such file or directory\n", 39);
		program->last_exit_status = 127;
		return (0);
	}
	program->last_exit_status = 0;
	print_envpath_list(*program->envpath, 0);
	return (0);
}
