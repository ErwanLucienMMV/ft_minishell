/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_for_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:08:50 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/08 01:00:44 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	get_key_len(char *s, int i)
{
	int	j;

	if (s[i + 1] == '?')
		return (1);
	if (ft_isdigit(s[i + 1]))
		return (1);
	if (!(ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
		return (0);
	j = i + 1;
	while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
		j++;
	return (j - i - 1);
}

static int	get_env_len(char *s, int i, t_envpath *ep)
{
	char	*key;
	char	*value;
	int		len;

	key = ft_substr(s, i + 1, get_key_len(s, i));
	if (!key)
		return (-1);
	value = get_env_value_by_key(&ep, key);
	len = 0;
	if (value)
		len = ft_strlen(value);
	free(key);
	return (len);
}

static int	process_exit_status(int status, int *t_count, int *i)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (-1);
	*t_count += ft_strlen(status_str);
	free(status_str);
	*i += 2;
	return (0);
}

static int	process_env_var(t_parser *n, t_envpath *ep, int *t_count, int *i)
{
	int	env_len;

	env_len = get_env_len(n->s, *i, ep);
	if (env_len < 0)
		return (-1);
	*t_count += env_len;
	*i += get_key_len(n->s, *i) + 1;
	return (0);
}

int	check_and_count_for_envvar(t_parser *n, t_envpath *ep, int status)
{
	int		i;
	int		t_count;

	i = 0;
	t_count = 0;
	while (n->s[i])
	{
		if (n->s[i] == '$' && n->s[i + 1] == '?')
		{
			if (process_exit_status(status, &t_count, &i) < 0)
				return (-1);
		}
		else if (n->s[i] == '$'
			&& (ft_isalnum(n->s[i + 1]) || n->s[i + 1] == '_'))
		{
			if (process_env_var(n, ep, &t_count, &i) < 0)
				return (-1);
		}
		else
		{
			t_count++;
			i++;
		}
	}
	return (t_count);
}
