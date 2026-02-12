/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:00:43 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/12 16:23:02 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "../libft/libft.h"
# include <stdio.h>

void	error_message_file_not_found(char *filename);
void	error_near_newline();
void	error_message_command_not_found(char *command);
void	error_near_pipe();
void	error_near_char(char *str);
#endif