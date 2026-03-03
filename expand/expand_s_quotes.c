/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_s_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 07:00:39 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/03 17:18:24 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_s_quote(t_parser **node, t_program *program)
{
	char	*new_str;
	int		len;

	(void)program;
	len = ft_strlen((*node)->s);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (1);
	ft_strlcpy(new_str, (*node)->s + 1, len - 1);
	free((*node)->s);
	(*node)->s = new_str;
	if (new_str[0] == '\0')
	{
		free(new_str);
		(*node)->s = ft_strdup("\'\'");
	}
	else
		(*node)->s = new_str;
	(*node)->type = WAS_SQUOTED;
	return (0);
}
