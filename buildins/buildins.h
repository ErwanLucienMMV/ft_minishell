/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:06 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/10 17:21:18 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include "../libft/libft.h"
# include "../parser/parser.h"
# include "../envpath/envpath.h"
# include "../terminal/program.h"
# include "../execve/execve.h"
# include <signal.h>
# include <readline/history.h>
# include <stdio.h>

//			--- Handle the env ---			//
int	buildin_export(t_parser *cmd, t_envpath *envpath, t_program *program);
int	buildin_unset(t_parser *cmd, t_envpath *envpath, t_program *program);
int	buildin_env(t_program *program);

int	buildin_echo(t_parser *cmd, t_program *program);

//			--- Handle the exit ---			//
int	buildin_exit(t_program *program);

//		--- Main buildin function ---		//
int	buildins(t_parser **parser, t_envpath *envpath, t_program *program);
int	check_buildin(t_parser *cmd, t_envpath *envpath, t_program *program);

#endif