/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_env_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:04:04 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/07 22:47:40 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	add_env_size(t_parser *node, t_envpath *envpath,
	int *i, int *size, int status)
{
	int		start;
	char	*key;
	char	*value;
	char	*status_str;

	start = ++(*i);
	if (node->s[*i] == '?')
		(*i)++;
	else
		while (node->s[*i] && (ft_isalnum(node->s[*i]) || node->s[*i] == '_'))
		(*i)++;
	key = ft_substr(node->s, start, *i - start);
	if (!key)
		return (1);
	status_str = NULL;
	if (key[0] == '?' && key[1] == '\0')
	{
		status_str = ft_itoa(status);
		if (!status_str)
			return (free(key), 1);
		*size += ft_strlen(status_str);
	}
	else
	{
		value = get_env_value_by_key(&envpath, key);
		if (value)
			*size += ft_strlen(value);
	}
	free(status_str);
	free(key);
	return (0);
}

int	calculate_final_size(t_parser *node, t_envpath *envpath, int len, int status)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	while (i < len - 1)
	{
		if (is_env_var(node, i))
		{
			if (add_env_size(node, envpath, &i, &size, status))
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
