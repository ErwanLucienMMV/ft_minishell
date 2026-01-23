/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:19:18 by abarthes          #+#    #+#             */
/*   Updated: 2025/11/13 13:07:12 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*mem_dest;

	mem_dest = (unsigned char *)dest;
	if (dest == src || size == 0)
		return (dest);
	else if (dest > src && dest <= src + size)
	{
		while (size--)
			mem_dest[size] = ((unsigned char *)src)[size];
	}
	else
		ft_memcpy(dest, src, size);
	return (dest);
}
