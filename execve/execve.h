/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:43:59 by abarthes          #+#    #+#             */
/*   Updated: 2026/02/12 12:47:59 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include "../libft/libft.h"
# include "../parser/parser.h"
# include "../envpath/envpath.h"
# include "../files_handler/fhandler.h"
# include "../terminal/program.h"
# include "../errors/errors.h"
# include <sys/wait.h>
# include "../buildins/buildins.h"

typedef struct s_commands
{
	t_parser			*cmd;
	char				**args;
	char				*infile;
	t_lexer				inputtype;
	char				*outfile;
	t_lexer				redir_type;
	struct s_commands	*next;
}	t_commands;

//			---freeing functions---		//
void			clearmatrix(char **tab);
void			free_t_parser(t_parser *parser);
void			free_t_command(t_commands *tofree);
void			clean_exit(char **splited_cmd, char *new_cmd);

//				---Utils---				//

void			do_command_piped(t_program *program,
					t_commands *cmd, char *path, char **envp);
void			handle_the_child(int pipe_fd[2],
					t_program *program, t_commands *cmd);
void			do_command(t_program *program,
					t_parser *cmd, char *path, char **envp);

//				---Children---			//
void			handle_middle_child(t_program *program,
					t_commands *cmd, int pipe_fd[2]);

//				---Checks---			//
int				there_is_at_least_one_pipe(t_parser *lineread);
int				count_cmd_args(t_parser *cmd);
int				is_a_buildin(char *cmd);
t_parser		*get_last_input_node(t_parser *parsed, t_lexer *input_type);

char			*find_command(char *command, char *pathline);
int				execve_handler(t_program *program);
void			do_command(t_program *program, t_parser *cmd,
					char *path, char **envp);
int				execve_with_pipe(t_program *program);
void			parse_commands_with_pipe(t_commands **commands,
					t_parser *parsed);
int				make_redirection(t_parser *parsed);


#endif