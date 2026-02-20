/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:00:43 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/20 08:24:13 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "../libft/libft.h"
# include <stdio.h>

void	error_message_file_not_found(char *filename);
void	error_near_newline(void);
void	error_message_command_not_found(char *command);
void	error_near_pipe(void);
void	error_near_char(char *str);

#endif