/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:19 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/17 16:12:51 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../parser/parser.h"
# include "../terminal/terminal.h"
# include "../envpath/envpath.h"


int		expand_plain_text(t_parser *node, t_envpath *envpath);
int		expand_d_quote(t_parser **node, t_envpath *envpath);
int		send_to_expand(t_parser **parsed, t_envpath *envpath, t_program *program);
void	set_node_type(t_parser *node);
int check_and_count_for_envvar(t_parser *n, t_envpath *ep);
int	restore_types_after_expansion(t_parser **tokens);
void		parser_clear_one(t_parser **node, t_program *program);
int		add_empty_nodes_to_their_next(t_program *program);
int	remove_useless_space_nodes(t_program *program);

#endif