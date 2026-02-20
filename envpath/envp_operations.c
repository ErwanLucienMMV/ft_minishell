/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:25:10 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 08:22:49 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envpath.h"

void	del_env_node_by_key(t_envpath **head, char *key)
{
	t_envpath	*temp;

	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		if (ft_strncmp(temp->index, key, ft_strlen(key)) == 0)
		{
			if (temp == *head)
				*head = temp->next;
			envp_delone(temp);
			return ;
		}
		temp = temp->next;
	}
}

char	*get_env_value_by_key(t_envpath **envpath, char *key)
{
	t_envpath	*temp;

	temp = *envpath;
	while (temp)
	{
		if (ft_strncmp(temp->index, key, ft_strlen(key))
			== 0 && ft_strlen(temp->index) == ft_strlen(key))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

int	print_envpath_list(t_envpath *envpath, int is_export)
{
	t_envpath	*temp;

	temp = envpath;
	while (temp)
	{
		if (temp->shown)
		{
			if (is_export && temp->value)
				printf("export %s=\"%s\"\n", temp->index, temp->value);
			else if (is_export && !temp->value)
				printf("export %s\n", temp->index);
			else if (!is_export && temp->value)
				printf("%s=%s\n", temp->index, temp->value);
		}
		temp = temp->next;
	}
	return (0);
}

t_envpath	*envp_copy(t_envpath *envpath)
{
	t_envpath	*copy;
	t_envpath	*temp;

	copy = NULL;
	temp = envpath;
	while (temp)
	{
		if (!new_envpath(&copy, temp->index, temp->value))
			return (NULL);
		temp = temp->next;
	}
	return (copy);
}

int	envp_clear(t_envpath **lst)
{
	t_envpath	*temp;
	t_envpath	*next;

	if (!lst || !*lst)
		return (0);
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		free(temp->index);
		free(temp->value);
		free(temp);
		temp = next;
	}
	*lst = 0;
	return (0);
}
