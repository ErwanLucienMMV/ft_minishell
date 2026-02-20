/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_envpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:15:48 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:16:09 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	buildin_env(t_program *program)
{
	if (get_env_value_by_key(program->envpath, "PATH") == NULL)
	{
		printf("minishell: env: No such file or directory\n");
		program->last_exit_status = 127;
		return (0);
	}
	program->last_exit_status = 0;
	print_envpath_list(*program->envpath, 0);
	return (0);
}
