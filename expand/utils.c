/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:02:06 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 08:02:05 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	restore_types_after_expansion(t_parser **tokens)
{
	t_parser	*cur;

	cur = *tokens;
	while (cur)
	{
		set_node_type(cur);
		cur = cur->next;
	}
	return (0);
}

int	copy_env_value(char *new_str, int *j, char *value)
{
	int	k;

	k = 0;
	while (value && value[k])
		new_str[(*j)++] = value[k++];
	return (0);
}
