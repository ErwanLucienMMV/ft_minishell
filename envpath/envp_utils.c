/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:21:35 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/27 17:51:56 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envpath.h"

static void	assign_temps_envpath(t_envpath *temp)
{
	char	*tmp_index;
	char	*tmp_value;

	tmp_index = temp->index;
	tmp_value = temp->value;
	temp->index = temp->next->index;
	temp->value = temp->next->value;
	temp->next->index = tmp_index;
	temp->next->value = tmp_value;
}

static void	print_and_clear_envp(t_envpath *copy)
{
	print_envpath_list(copy, 1);
	envp_clear(&copy);
}

int	print_envpath_list_sorted(t_envpath *envpath)
{
	t_envpath	*copy;
	t_envpath	*temp;
	int			swapped;

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
			if (ft_strncmp(temp->index, temp->next->index,
					ft_strlen(temp->index)) > 0)
			{
				assign_temps_envpath(temp);
				swapped = 1;
			}
			temp = temp->next;
		}
	}
	print_and_clear_envp(copy);
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

void	update_pwd_and_oldpwd(t_envpath *envpath)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("getcwd"), (void)0);
	oldpwd = get_env_value_by_key(&envpath, "PWD");
	if (oldpwd)
	{
		if (new_envpath(&envpath, "OLDPWD", oldpwd) == 0)
			return (free(pwd), (void)0);
	}
	else
	{
		if (new_envpath(&envpath, "OLDPWD", "") == 0)
			return (free(pwd), (void)0);
	}
	if (new_envpath(&envpath, "PWD", pwd) == 0)
		return ;
	free(pwd);
}
