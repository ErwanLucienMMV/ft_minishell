/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:30:25 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/23 16:31:19 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	error_message_is_a_directory(char *filename)
{
	ft_printf_fd(2, "miniswag: %s: Is a directory\n", filename);
}
