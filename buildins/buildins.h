/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:41:06 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/26 12:26:44 by emaigne          ###   ########.fr       */
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
int		buildin_export(t_parser *cmd, t_envpath *envpath, t_program *program);
int		buildin_unset(t_parser *cmd, t_envpath *envpath, t_program *program);
int		buildin_env(t_program *program);

int		buildin_echo(t_parser *cmd, t_program *program);

//			--- Handle the exit ---			//
void	free_envpath(t_envpath *envpath);
void	free_parsers(t_parser *parser);
int		buildin_exit(t_program *program);
int		check_buildin_piped(t_parser *cmd,
			t_envpath *envpath, t_program *program);
int		check_for_exit_arguments(t_program *p);
int		is_numeric_string(char *str);

//		--- Main buildin function ---		//
int		buildins(t_parser **parser, t_envpath *envpath, t_program *program);
int		check_buildin(t_parser *cmd, t_envpath *envpath, t_program *program);
int		buildin_pwd(t_program *program);

//			--- Handle the cd ---			//
int		buildin_cd(t_parser *cmd, t_envpath *envpath, t_program *program);

#endif