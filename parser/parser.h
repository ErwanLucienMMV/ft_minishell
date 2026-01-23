/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:53:07 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/23 17:42:35 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"

typedef struct s_parser
{
	lexer		type;
	char		*s;
	struct s_parser	*next;
	struct s_parser	*prev;
} t_parser;


t_parser	*parsing(char *s);

#endif