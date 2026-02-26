/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:30:47 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/24 14:27:02 by emaigne          ###   ########.fr       */
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
}	t_envpath;

//			---free utils---			//
void		free_matrix(char **tab);

//			---Operations---			//
void		del_env_node_by_key(t_envpath **head, char *key);
char		*get_env_value_by_key(t_envpath **envpath, char *key);
int			print_envpath_list(t_envpath *envpath, int is_export);
t_envpath	*envp_copy(t_envpath *envpath);
int			envp_clear(t_envpath **lst);

int			create_envpath_list(t_envpath **envpath, char **envp);
int			new_envpath(t_envpath **head, char *index, char *value);

int			print_envpath_list(t_envpath *envpath, int is_export);
int			print_envpath_list_sorted(t_envpath *envpath);
void		envp_delone(t_envpath *node);
void		del_env_node_by_key(t_envpath **head, char *key);
void		update_pwd_and_oldpwd(t_envpath *envpath);

#endif