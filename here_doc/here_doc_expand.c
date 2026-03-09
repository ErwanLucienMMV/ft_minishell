/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:55:01 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/09 16:13:10 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*expand_exit_status_var(t_program *program, char *line,
	int i, int *new_i)
{
	char	*status_str;
	char	*prefix;
	char	*result;

	status_str = ft_itoa(program->last_exit_status);
	if (!status_str)
		return (free(line), NULL);
	prefix = ft_strndup(line, i);
	result = ft_strjoin_gnl(prefix, status_str);
	free(status_str);
	*new_i = ft_strlen(result);
	result = ft_strjoin_gnl(result, line + i + 2);
	free(line);
	return (result);
}

static char	*expand_one_var(t_program *program, char *line, int i, int *new_i)
{
	char	*env_value;
	char	*key;
	char	*prefix;
	char	*result;
	int		j;

	j = i + 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = ft_strndup(line + i + 1, j - i - 1);
	env_value = get_env_value_by_key(program->envpath, key);
	free(key);
	if (!env_value)
		env_value = "";
	prefix = ft_strndup(line, i);
	result = ft_strjoin_gnl(prefix, env_value);
	*new_i = ft_strlen(result);
	result = ft_strjoin_gnl(result, line + j);
	free(line);
	return (result);
}

char	*expand_line(t_program *program, char *line, t_parser *lineread)
{
	int		i;
	int		new_i;

	(void)lineread;
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			line = expand_exit_status_var(program, line, i, &new_i);
			if (!line)
				return (NULL);
			i = new_i;
			continue ;
		}
		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
		{
			line = expand_one_var(program, line, i, &new_i);
			i = new_i;
			continue ;
		}
		i++;
	}
	return (line);
}
