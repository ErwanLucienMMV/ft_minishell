/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:53:07 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 15:47:23 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include <stdio.h>
# include "../errors/errors.h"

typedef struct s_parser
{
	t_lexer			type;
	char			*s;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

# ifndef IS_DEBUG
#  define IS_DEBUG 0
# endif

//				---Debug---					//
void		print_error(t_parser *temp);

//				---Operations---			//
int			parser_clear(t_parser **lst);
void		parser_add_back(t_parser **lst, t_parser *new);
t_parser	*parser_node_new(t_lexer type, char *s, int x);
int			its_env_var(t_parser **head, char *s, int *i);

//				---check_its---				//
int			its_d_quote(t_parser **head, char *s, int *i);
int			its_s_quote(t_parser **head, char *s, int *i);
int			its_exit_status(t_parser **head, char *s, int *i);
int			its_pipe(t_parser **head, char *s, int *i);
int			its_command(t_parser **head, char *s, int *i);

//				---Utils---					//
int			new_parser(t_parser **head, t_parser *new_node);

t_parser	*parsing(char *s);
t_parser	*parsing_after_expand(char *s, int there_is_echo);

int			parser_clear(t_parser **lst);
t_parser	*get_first_parser(t_parser *lst);
t_parser	*get_last_parser(t_parser *lst);

//			---Sanitize---					//
//		---Single token functions---		//
int			sanitize_redir_input(t_parser *token);
int			sanitize_redir_output(t_parser *token);
int			sanitize_redir_output_app(t_parser *token);
int			sanitize_delimiter(t_parser *token);

int			sanitize(t_parser **head);
t_parser	*get_prev_echo(t_parser *node);

t_parser	*get_next_token_non_space(t_parser *token);
t_parser	*get_prev_token_non_space(t_parser *token);

t_parser	*get_next_non_space(t_parser *token);
t_parser	*get_prev_non_space(t_parser *token);

#endif