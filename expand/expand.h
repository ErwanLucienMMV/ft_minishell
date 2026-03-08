/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:19 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:08:58 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../parser/parser.h"
# include "../terminal/terminal.h"
# include "../envpath/envpath.h"

typedef struct s_expand_data
{
	t_parser	*node;
	t_envpath	*envpath;
	char		*new_str;
	int			*indices;
	int			status;
}	t_expand_data;

typedef struct s_env_calc
{
	t_parser	*node;
	t_envpath	*envpath;
	int			*i;
	int			*size;
	int			status;
}	t_env_calc;

typedef struct s_dquote_data
{
	t_parser	*node;
	t_envpath	*envpath;
	char		*new_str;
	int			*indice;
	t_program	*program;
}	t_dquote_data;

//			---expand types functions---	//
int		expand_plain_text(t_parser *node, t_envpath *envpath,
			t_program *program);
int		expand_d_quote(t_parser **node, t_envpath *envpath,
			t_program *program);
int		expand_s_quote(t_parser **node, t_program *program);
int		expand_env_var(t_parser **node, t_envpath *envpath, t_program *program);

int		send_to_expand(t_envpath *envpath, t_program *program);
int		restore_types_after_expansion(t_parser **tokens);

//		----Nodes operations---				//
void	parser_clear_one(t_parser **node, t_program *program);
int		add_empty_nodes_to_their_next(t_program *program);
void	free_and_reset_node(t_parser *node, char *new_str);
void	set_node_type(t_parser *node);
int		remove_useless_space_nodes(t_program *program);
void	mark_expanded_nodes(t_parser *start, t_parser *stop);
int		replace_with_expansion(t_parser **node,
			t_parser *expanded_one);
void	attach_tail(t_parser *node, t_parser *next);

//			---Utils---						//
int		copy_env_value(char *new_str, int *j, char *value);

//			---Checks---					//
int		is_env_var(t_parser *node, int i);
int		check_and_count_for_envvar(t_parser *n, t_envpath *ep, int status);

int		calculate_final_size(t_parser *node, t_envpath *envpath,
			int len, int status);
int		merge_nodes(t_program *program, t_parser *cur, int len);
int		is_expanded_type(t_lexer type);
int		group_has_is_delimiter(t_parser *cur);
void	strip_quotes_if_no_delimiter(t_parser *cur);
char	*wrap_with_quote(char *s, char quote);
int		add_quotes_for_delimiter(t_parser *cur);

//			---expand_plain_text utils---	//
int		contains_env_var(const char *s);
int		get_key_end(char *s, int start);
char	*get_value(char *key, t_envpath *envpath, int status);
int		is_expandable(char c);
int		reparse_and_replace(t_parser *node);

//			---add_empty_nodes utils---		//
int		is_redir_type(t_lexer type);
int		calc_group_len(t_parser *cur);

//			---expand_d_quote utils---		//
int		append_value(char **new_str, int *indice, char *value);

#endif