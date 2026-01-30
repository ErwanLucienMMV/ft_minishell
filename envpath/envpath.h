/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:30:47 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/30 14:48:12 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVPATH_H
# define ENVPATH_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_envpath
{
	char				*index;
	char				*value;
	int					shown;
	struct s_envpath	*next;
	struct s_envpath	*prev;
} t_envpath;

int 	create_envpath_list(t_envpath **envpath, char **envp);
int		new_envpath(t_envpath **head, char *index, char *value);

char	*get_env_value_by_key(t_envpath *envpath, char *key);
int		print_envpath_list(t_envpath *envpath, int is_export);
int		print_envpath_list_sorted(t_envpath *envpath);
void	envp_delone(t_envpath *node);
void	del_env_node_by_key(t_envpath **head, char *key);

#endif