/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_env_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:04:04 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/08 00:56:39 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	get_env_key_end(char *s, int start)
{
	int	i;

	i = start;
	if (s[i] == '?')
		i++;
	else
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	return (i);
}

static int	add_status_size(char *key, int *size, int status)
{
	char	*status_str;

	if (key[0] == '?' && key[1] == '\0')
	{
		status_str = ft_itoa(status);
		if (!status_str)
			return (1);
		*size += ft_strlen(status_str);
		free(status_str);
		return (1);
	}
	return (0);
}

static int	add_env_size(t_env_calc *calc)
{
	int		start;
	char	*key;
	char	*value;

	start = ++(*calc->i);
	*calc->i = get_env_key_end(calc->node->s, *calc->i);
	key = ft_substr(calc->node->s, start, *calc->i - start);
	if (!key)
		return (1);
	if (add_status_size(key, calc->size, calc->status))
	{
		free(key);
		return (0);
	}
	value = get_env_value_by_key(&calc->envpath, key);
	if (value)
		*calc->size += ft_strlen(value);
	free(key);
	return (0);
}

int	calculate_final_size(t_parser *node,
	t_envpath *envpath, int len, int status)
{
	t_env_calc	calc;
	int			i;
	int			size;

	i = 1;
	size = 0;
	calc = (t_env_calc){node, envpath, &i, &size, status};
	while (i < len - 1)
	{
		if (is_env_var(node, i))
		{
			if (add_env_size(&calc))
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
