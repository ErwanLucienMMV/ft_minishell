/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:04:34 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 06:41:48 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../parser/parser.h"
# include "../buildins/buildins.h"
# include "../envpath/envpath.h"
# include "../expand/expand.h"
# include "../signals/signals.h"
# include "../files_handler/fhandler.h"
# include "../here_doc/here_doc.h"
# include "../execve/execve.h"

# if defined(__APPLE__)
/* On some macOS setups the readline header (or libedit compatibility) may
	not declare these functions; provide minimal prototypes to avoid
	implicit-declaration errors at compile time. */
void		rl_replace_line(const char *text, int clear_undo);
void		rl_redisplay(void);
# endif

# ifndef IS_DEBUG
#  define IS_DEBUG 0
# endif

//					---DEBUG---				//
void		print_debug(t_program *program);

//					---checks---			//
int			check_at_least_one_node(t_program *program);

//					---Handlers---			//
int			handle_redirections(t_program *program);
void		handle_expansions(t_program *program);
void		execute_and_restore(t_program *program);

#endif