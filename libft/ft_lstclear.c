/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:27:24 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 16:12:23 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*lst_next;

	lst_next = *lst;
	temp = *lst;
	while (lst_next)
	{
		del(lst_next->content);
		temp = lst_next;
		lst_next = lst_next->next;
		free(temp);
	}
	*lst = 0;
}
