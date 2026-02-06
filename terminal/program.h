/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:42:43 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/04 02:32:50 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include "../parser/parser.h"
# include "../envpath/envpath.h"

typedef struct s_program
{
	t_parser	**parsed;
	t_envpath	**envpath;
	int			saved_stdin;
	int			saved_stdout;
	char		*here_doc_tempfile;
	int			last_exit_status;
	char		**envp;
}	t_program;

#endif