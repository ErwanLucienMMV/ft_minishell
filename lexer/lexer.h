/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:34:18 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/03 17:18:08 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"

typedef enum e_lexer
{
	CMD,
	CMD_ARG,
	FILENAME,
	ENVVAR,
	SQUOTE,
	DQUOTE,
	PIPE,
	EXIT_STATUS,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APP,
	DELIMITER,
	IS_DELIMITER,
	T_SPACE,
	WAS_EXPANDED,
	WAS_SQUOTED,
	WAS_DQUOTED
}	t_lexer;

#endif