/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:29:58 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/02 16:14:04 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# define HERE_DOC_TMPFILE ".here_doc_tempfile"

# include "../libft/libft.h"
# include "../parser/parser.h"
# include <fcntl.h>
# include <readline/readline.h>
# include "../envpath/envpath.h"
# include "../terminal/program.h"
# include "../signals/signals.h"

int		doing_here_doc_util(t_program *program, t_parser *lineread,
			char *tempfile, int mode);
int		doing_here_doc(t_program *program, char *tempfile);
char	*expand_line(t_program *program, char *line, t_parser *lineread);
void	sigint_handler_heredoc(int signal);
void	create_signal(void);
int		handle_signal(t_program *program, int fd, char *line);

#endif