/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_env_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:04:04 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 16:34:28 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	add_env_size(t_parser *node, t_envpath *envpath,
	int *i, int *size)
{
	int		start;
	char	*key;
	char	*value;

	start = ++(*i);
	while (node->s[*i] && ft_isalnum(node->s[*i]))
		(*i)++;
	key = ft_substr(node->s, start, *i - start);
	if (!key)
		return (1);
	value = get_env_value_by_key(&envpath, key);
	if (value)
		*size += ft_strlen(value);
	free(key);
	return (0);
}

int	calculate_final_size(t_parser *node, t_envpath *envpath, int len)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	while (i < len - 1)
	{
		if (is_env_var(node, i))
		{
			if (add_env_size(node, envpath, &i, &size))
				return (-1);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}
