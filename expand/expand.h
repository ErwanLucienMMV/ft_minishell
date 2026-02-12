/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:19 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/12 18:48:27 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../parser/parser.h"
# include "../terminal/terminal.h"
# include "../envpath/envpath.h"
# include "../terminal/program.h"

int		expand_plain_text(t_parser *node, t_envpath *envpath);
int		expand_d_quote(t_parser *node, t_envpath *envpath);
int		send_to_expand(t_parser **parsed, t_envpath *envpath, t_program *program);
void	set_node_type(t_parser *node);

#endif