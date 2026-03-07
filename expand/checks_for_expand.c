/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_for_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:08:50 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/07 21:18:25 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	get_key_len(char *s, int i)
{
	int	j;

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

int	check_and_count_for_envvar(t_parser *n, t_envpath *ep)
{
	int	i;
	int	t_count;
	int	env_len;

	i = 0;
	t_count = 0;
	while (n->s[i])
	{
		if (n->s[i] == '$'
			&& (ft_isalnum(n->s[i + 1]) || n->s[i + 1] == '_'))
		{
			env_len = get_env_len(n->s, i, ep);
			if (env_len < 0)
				return (-1);
			t_count += env_len;
			i += get_key_len(n->s, i) + 1;
		}
		else
		{
			t_count++;
			i++;
		}
	}
	return (t_count);
}

int	is_env_var(t_parser *node, int i)
{
	return (node->s[i] == '$'
		&& (ft_isalnum(node->s[i + 1]) || node->s[i + 1] == '_'));
}
