/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:04:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/16 12:44:59 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "program.h"

volatile sig_atomic_t	g_signal;

int	handle_sigint(char *line)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		if (line)
			free(line);
		return (1);
	}
	return (0);
}

int	init_program(t_program **program, char **envp)
{
	*program = ft_calloc(1, sizeof(t_program));
	if (!*program)
		return (0);
	(*program)->parsed = ft_calloc(1, sizeof(t_parser *));
	if (!(*program)->parsed)
		return (0);
	(*program)->envpath = ft_calloc(1, sizeof(t_envpath *));
	if (!(*program)->envpath)
		return (0);
	*(*program)->envpath = NULL;
	(*program)->envp = envp;
	if (create_envpath_list((*program)->envpath, envp) == 0)
		return (buildin_exit(*program), 0);
	if (new_envpath((*program)->envpath, "OLDPWD", "") == 0)
		buildin_exit(*program);
	return (1);
}

int	process_parsing_and_sanitize(t_program *program, char *line)
{
	*program->parsed = parsing(line);
	if (!(*program->parsed) || sanitize(program->parsed))
	{
		parser_clear(program->parsed); 
		return (1); 
	}
	return (0);
}

int	check_at_least_one_node(t_program *program)
{
	*(program->parsed) = get_first_parser(*(program->parsed));
	if (!*(program->parsed))
		return (1);
	return (0);
}

void	main_loop(t_program *program)
{
	char	*line;

	while (1)
	{
		set_signal_action();
		line = readline("$miniswag> ");
		// if (handle_sigint(line))
		// 	continue ;
		if (!line)
			break ;
		if (line && *line)
		{
			add_history(line);
			if (process_parsing_and_sanitize(program, line))
			{
				free(line);
				continue ;
			}
			free(line);
			handle_expansions(program);
			if (check_at_least_one_node(program))
				continue ;
			if (handle_redirections(program))
				continue ;
			execute_and_restore(program);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_program	*program;

	(void)argc;
	(void)argv;
	program = NULL;
	if (!init_program(&program, envp))
		buildin_exit(program);
	tcgetattr(STDIN_FILENO, &program->g_term_orig);
	main_loop(program);
	buildin_exit(program);
}
