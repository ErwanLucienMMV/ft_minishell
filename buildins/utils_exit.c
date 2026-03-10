/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:47:56 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/10 18:21:56 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include <limits.h>

void	ft_exit(t_program *program)
{
	rl_clear_history();
	if (program->here_doc_tempfile)
		unlink(program->here_doc_tempfile);
	if (program->saved_stdin != -1)
		close (program->saved_stdin);
	if (program->saved_stdout != -1)
		close (program->saved_stdout);
}

int	return_exit_status(int sign, unsigned long long result, long *value)
{
	if (sign == -1 && result == (unsigned long long)LONG_MAX + 1ULL)
		*value = LONG_MIN;
	else
		*value = (long)(result * sign);
	return (1);
}

int	parse_exit_status(char *str, long *value)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;

	if (!str || !*str)
		return (0);
	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		sign = 1 - 2 * (str[i++] == '-');
	if (!str[i])
		return (0);
	result = 0;
	limit = LONG_MAX;
	if (sign == -1)
		limit = (unsigned long long)LONG_MAX + 1ULL;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || result > (limit - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (return_exit_status(sign, result, value));
}
