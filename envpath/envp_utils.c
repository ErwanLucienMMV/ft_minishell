/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:21:35 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/30 14:47:38 by abarthes         ###   ########.fr       */
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

char	*get_env_value_by_key(t_envpath *envpath, char *key)
{
	t_envpath	*temp;

	temp = envpath;
	while (temp)
	{
		if (ft_strncmp(temp->index, key, ft_strlen(key)) == 0)
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
			if (is_export)
				printf("export %s=\"%s\"\n", temp->index, temp->value);
			else
				printf("%s=%s\n", temp->index, temp->value);
		}
		temp = temp->next;
	}
	return (0);
}

t_envpath	*envp_copy(t_envpath *envpath)
{
	t_envpath   *copy;
	t_envpath   *temp;

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

int	print_envpath_list_sorted(t_envpath *envpath)
{
	t_envpath	*copy;
	t_envpath	*temp;
	int			swapped;
	char 		*tmp_index;
	char 		*tmp_value;

	copy = envp_copy(envpath);
	if (!copy)
		return (1);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		temp = copy;
		while (temp && temp->next)
		{
			if (ft_strncmp(temp->index, temp->next->index, ft_strlen(temp->index)) > 0)
			{
				tmp_index = temp->index;
				tmp_value = temp->value;
				temp->index = temp->next->index;
				temp->value = temp->next->value;
				temp->next->index = tmp_index;
				temp->next->value = tmp_value;
				swapped = 1;
			}
			temp = temp->next;
		}
	}
	print_envpath_list(copy, 1);
	envp_clear(&copy);
	return (0);
}

void	envp_delone(t_envpath *node)
{
	t_envpath	*prev;
	t_envpath	*next;

	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(node->index);
	free(node->value);
	free(node);
}
