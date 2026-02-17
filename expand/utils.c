/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:02:06 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/17 16:23:27 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	remove_useless_space_nodes(t_program *program)
{
	t_parser	*cur;
	t_parser	*next;

	cur = *program->parsed;
	while (cur)
	{
		next = cur->next;
		if (cur->type == SPACE)
		{
			parser_clear_one(&cur, program);
		}
		cur = next;
	}
	return (0);
}

int	restore_types_after_expansion(t_parser **tokens)
{
	t_parser	*cur;

	cur = *tokens;
	while (cur)
	{
		set_node_type(cur);
		cur = cur->next;
	}
	return (0);
}

int	add_empty_nodes_to_their_next(t_program *program)
{
	t_parser	*cur;
	t_parser	*to_remove;
	t_parser	*expanded;
	char	*str;
	int		count;
	int		buf_size;

	print_debug(program);
	cur = *(program->parsed);
	while (cur)
	{
		if (cur->type == SPACE)
		{
			cur = cur->next;
			continue ;
		}
		expanded = cur->next;
		count = ft_strlen(cur->s);
		while (expanded && expanded->type != SPACE)
		{
			count += ft_strlen(expanded->s);
			expanded = expanded->next;
		}
		if (!expanded || expanded->type == SPACE)
		{
			expanded = cur->next;
			if (expanded && expanded->type != SPACE)
			{
				buf_size = count + 1;
				str = malloc(buf_size * sizeof(char));
				if (!str)
					return (1);
				str[0] = '\0';
				ft_strlcat(str, cur->s, buf_size);
				while (expanded && expanded->type != SPACE)
				{
					to_remove = expanded;
					ft_strlcat(str, expanded->s, buf_size);
					expanded = expanded->next;
					parser_clear_one(&to_remove, program);
				}
				free(cur->s);
				cur->s = str;
				cur->next = expanded;
			}
		}
		cur = cur->next;
	}
	return (0);
}
