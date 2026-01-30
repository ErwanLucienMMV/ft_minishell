/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:49:27 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/30 15:50:00 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_plain_text(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (node->s[i] == '$' && ft_isalnum(node->s[i + 1]))
		{
			int start = i + 1;
			while (node->s[start] && ft_isalnum(node->s[start]))
				start++;
			char *key = ft_substr(node->s, i + 1, start - (i + 1));
			char *value = get_env_value_by_key(envpath, key);
			free(key);
			if (value)
			{
				int k = 0;
				while (value[k])
					new_str[j++] = value[k++];
			}
			i = start;
		}
		else
			new_str[j++] = node->s[i++];
	}
	new_str[j] = '\0';
	free(node->s);
	node->s = new_str;
	return (0);
}	


int	expand_exit_status(t_parser *node, int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (1);
	free(node->s);
	node->s = status_str;
	return (0);
}

int	expand_env_var(t_parser *node, t_envpath *envpath)
{
	char	*value;

	value = get_env_value_by_key(envpath, node->s);
	if (value)
	{
		free(node->s);
		node->s = ft_strdup(value);
		if (node->prev && node->prev->type == CMD)
			node->type = CMD_ARG;
		else
			node->type = CMD;
	}
	else
	{
		free(node->s);
		node->s = ft_strdup("");
		if (node->prev && node->prev->type == CMD)
			node->type = CMD_ARG;
		else
			node->type = CMD;
	}
	return (0);
}

int	expand_d_quote(t_parser *node, t_envpath *envpath)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (1);
	i = 1;
	j = 0;
	while (i < len - 1)
	{
		if (node->s[i] == '$' && ft_isalnum(node->s[i + 1]))
		{
			int start = i + 1;
			while (node->s[start] && ft_isalnum(node->s[start]))
				start++;
			char *key = ft_substr(node->s, i + 1, start - (i + 1));
			char *value = get_env_value_by_key(envpath, key);
			char *temp = malloc((ft_strlen(new_str) + ft_strlen(value)) * sizeof(char));
			ft_strlcpy(temp, new_str, j + 1);
			free(new_str);
			new_str = temp;
			free(key);
			if (value)
			{
				int k = 0;
				while (value[k])
					new_str[j++] = value[k++];
			}
			i = start;
		}
		else
			new_str[j++] = node->s[i++]; 
	}
	new_str[j] = '\0';
	free(node->s);
	node->s = new_str;
	if (j == 0)
		parser_clear_one(node);
	if (node->prev && node->prev->type == CMD)
		node->type = CMD_ARG;
	else
		node->type = CMD;
	return (0);
}

int	expand_s_quote(t_parser *node)
{
	char	*new_str;
	int		len;

	len = ft_strlen(node->s);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (1);
	ft_strlcpy(new_str, node->s + 1, len - 1);
	free(node->s);
	node->s = new_str;
	if (node->prev && node->prev->type == CMD)
		node->type = CMD_ARG;
	else
		node->type = CMD;
	return (0);
}

int	send_to_expand(t_parser **parsed, t_envpath *envpath)
{
	//expand logic here
	t_parser	*temp;

	temp = *parsed;
	while (temp)
	{
		if (temp->type == ENVVAR)
			expand_env_var(temp, envpath);
		else if (temp->type == DQUOTE)
			expand_d_quote(temp, envpath);
		else if (temp->type == SQUOTE)
			expand_s_quote(temp);
		else if (temp->type == EXIT_STATUS)
			expand_exit_status(temp, 0);
		else if (temp->type == CMD || temp->type == CMD_ARG)
			expand_plain_text(temp, envpath);
		temp = temp->next;
	}
	return (0);
}