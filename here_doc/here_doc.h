/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:29:58 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/27 15:26:55 by abarthes         ###   ########.fr       */
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

int	doing_here_doc_util(t_program *program, t_parser *lineread, char *tempfile, int mode);
int	doing_here_doc(t_program *program, char *tempfile);

#endif