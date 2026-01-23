/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:43:52 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 17:28:09 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*result;
	void	*tmp;

	list = 0;
	while (lst)
	{
		tmp = f(lst->content);
		if (!tmp)
		{
			ft_lstclear(&list, del);
			return (0);
		}
		result = ft_lstnew(tmp);
		if (!result)
		{
			ft_lstclear(&list, del);
			return (0);
		}
		ft_lstadd_back(&list, result);
		lst = lst->next;
	}
	return (list);
}
