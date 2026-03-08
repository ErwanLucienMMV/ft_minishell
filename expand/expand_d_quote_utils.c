/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_d_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:45:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:08:58 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	append_value(char **new_str, int *indice, char *value)
{
	int	k;

	k = 0;
	while (value && value[k])
		(*new_str)[indice[1]++] = value[k++];
	return (0);
}
