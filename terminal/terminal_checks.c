/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:40:33 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 06:41:00 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	check_at_least_one_node(t_program *program)
{
	*(program->parsed) = get_first_parser(*(program->parsed));
	if (!*(program->parsed))
		return (1);
	return (0);
}
