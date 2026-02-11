/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:04:41 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/11 08:50:52 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "program.h"

volatile sig_atomic_t	g_signal;

//handle the exit cleanly, this is what happens when CTRL + D for example
/*
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_program	*program;

	argc = 0;
	argv = NULL;
	program = ft_calloc(sizeof(t_program));
	if (!program)
		buildin_exit(program);
	program->parsed = ft_calloc(sizeof(t_parser *));
	if (!program->parsed)
		buildin_exit(program);
	program->envp = envp;
	program->envpath = ft_calloc(sizeof(t_envpath *));
	if (!program->envpath)
		buildin_exit(program);
	*(program->envpath) = NULL;
	if (create_envpath_list(program->envpath, envp) == 0)
		return (1);
	while (1)
	{
		set_signal_action();
		line = readline("$miniswag> ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			if (line)
				free(line);
			continue ;
		}
		if (!line)
			break ;
		if (line && *line)
		{
			add_history(line);
			*(program->parsed) = parsing(line);
			free(line);
			if (!program->parsed || !sanitize(program->parsed))
				printf("syntax error\n");
			else
			{
				print_debug(program);
				send_to_expand(program->parsed, *(program->envpath), program);
				print_debug(program);
				program->saved_stdin = dup(STDIN_FILENO);
				program->saved_stdout = dup(STDOUT_FILENO);
				file_handler(program->parsed);
				program->here_doc_tempfile = ".here_doc_tempfile";
				doing_here_doc(program->parsed);
				buildins(program->parsed, *(program->envpath), program);
				execve_handler(program);
				rl_replace_line("", 0);
				rl_redisplay();
				dup2(program->saved_stdin, STDIN_FILENO);
				dup2(program->saved_stdout, STDOUT_FILENO);
				close(program->saved_stdin);
				close(program->saved_stdout);
				parser_clear(program->parsed);
			}
		}
	}
	return (0);
}
*/

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
	if (!program->parsed)
		return (0);
	if (!sanitize(program->parsed))
	{
		printf("syntax error\n");
		return (0);
	}
	return (1);
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
			if (!process_parsing_and_sanitize(program, line))
			{
				free(line);
				continue ;
			}
			free(line);
			handle_expansions(program);
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
