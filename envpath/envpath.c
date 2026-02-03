/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:31:45 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/03 13:50:28 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envpath.h"
#include <stdio.h>

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

	new = malloc(sizeof(t_envpath));
	if (!new)
		return (0);
	new->index = ft_strdup(index);
	new->value = ft_strdup(value);
	new->shown = 1;
	new->prev = 0;
	new->next = 0;
	return (new);
}

int	new_envpath(t_envpath **head, char *index, char *value)
{
	t_envpath	*new_node;

	if (get_env_value_by_key(head, index))
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
			if (new_envpath(envpath, array[0], array[1]) == 0)
				return (0);
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
