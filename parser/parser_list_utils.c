/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:40:00 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 01:06:02 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_env_var_len(char *s)
{
	int	x;

	x = 1;
	if (ft_isdigit(s[1]))
		x = 2;
	else if (ft_isalpha(s[1]) || s[1] == '_')
	{
		x = 2;
		while (s[x] && (ft_isalnum(s[x]) || s[x] == '_'))
			x++;
	}
	return (x);
}
