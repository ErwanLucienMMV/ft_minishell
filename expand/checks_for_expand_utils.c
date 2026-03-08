/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_for_expand_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:15:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:00:44 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	is_env_var(t_parser *node, int i)
{
	return (node->s[i] == '$'
		&& (ft_isalnum(node->s[i + 1])
			|| node->s[i + 1] == '_'
			|| node->s[i + 1] == '?'));
}
