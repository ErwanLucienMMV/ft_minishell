/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:29:58 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/17 21:10:24 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# define HERE_DOC_TMPFILE ".here_doc_tempfile"

# include "../libft/libft.h"
# include "../parser/parser.h"
# include <fcntl.h>
# include <readline/readline.h>

int	doing_here_doc(t_parser **lineread, char *tempfile);

#endif