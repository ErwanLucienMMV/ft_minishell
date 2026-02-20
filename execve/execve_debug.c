/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:44:52 by emaigne           #+#    #+#             */
/*   Updated: 2026/02/20 12:03:02 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	print_parser_node(t_parser *elem)
{
	if (IS_DEBUG)
	{
		if (!elem)
		{
			ft_printf_fd(2, "no t_parser provided\n");
			return ;
		}
		ft_printf_fd(2, "t_parser string: %s\n", elem->s);
	}
}

void	print_matrix(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_printf_fd(2, "%s\n", tab[i]);
		i++;
	}
}

void	print_command_list(t_commands **head)
{
	t_commands	*elem;
	int			i;

	i = 0;
	elem = *head;
	if (IS_DEBUG)
	{
		while (elem)
		{
			ft_printf_fd(2, "%dth of the list:\n", i++);
			print_parser_node(elem->cmd);
			print_matrix(elem->args);
			ft_printf_fd(2, "Infile: %s\nOufile: %s\n\n",
				elem->infile, elem->outfile);
			elem = elem->next;
		}
		ft_printf_fd(2, "End of debug informations\n");
	}
}
