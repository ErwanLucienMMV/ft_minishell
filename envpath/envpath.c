/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:31:45 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/24 14:29:11 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envpath.h"
#include <stdio.h>

int	already_in_env(t_envpath **envpath, char *index)
{
	t_envpath	*temp;

	temp = *envpath;
	while (temp)
	{
		if (ft_strncmp(temp->index, index, ft_strlen(index)) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	envp_add_back(t_envpath **lst, t_envpath *new)
{
	t_envpath	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

t_envpath	*envp_node_new(char *index, char *value)
{
	t_envpath	*new;

	new = ft_calloc(1, sizeof(t_envpath));
	if (!new)
		return (NULL);
	new->index = ft_strdup(index);
	if (!new->index)
		return (free(new), NULL);
	if (!value)
		new->value = NULL;
	else
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->index), free(new), NULL);
	}
	new->shown = 1;
	new->prev = 0;
	new->next = 0;
	return (new);
}

int	new_envpath(t_envpath **head, char *index, char *value)
{
	t_envpath	*new_node;

	if (already_in_env(head, index))
		del_env_node_by_key(head, index);
	new_node = envp_node_new(index, value);
	if (!new_node)
		return (0);
	envp_add_back(head, new_node);
	return (1);
}

int	create_envpath_list(t_envpath **envpath, char **envp)
{
	int		i;
	char	**array;
	int		j;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			array = ft_split(envp[i], '=');
			if (!array)
				return (0);
			if (new_envpath(envpath, array[0], array[1]) == 0)
				return (free_matrix(array), 0);
			if (array)
			{
				j = -1;
				while (array[++j])
					free(array[j]);
				free(array);
			}
		}
		i++;
	}
	return (1);
}
