/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:30:51 by abarthes          #+#    #+#             */
/*   Updated: 2026/03/02 14:26:39 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

extern volatile sig_atomic_t	g_signal;

char *ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*expand_one_var(t_program *program, char *line, int i, int *new_i)
{
	char	*env_value;
	char	*key;
	char	*prefix;
	char	*result;
	char	*tmp;
	int		j;

	j = i + 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = ft_strndup(line + i + 1, j - i - 1);
	env_value = get_env_value_by_key(program->envpath, key);
	free(key);
	if (!env_value)
		env_value = "";
	prefix = ft_strndup(line, i);
	tmp = ft_strjoin(prefix, env_value);
	*new_i = ft_strlen(tmp);
	free(prefix);
	result = ft_strjoin(tmp, line + j);
	free(tmp);
	free(line);
	return (result);
}

char	*expand_line(t_program *program, char *line, t_parser *lineread)
{
	int		i;
	int		new_i;

	(void)lineread;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
		{
			line = expand_one_var(program, line, i, &new_i);
			i = new_i;
			continue ;
		}
		i++;
	}
	return (line);
}

void	sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(2, "\n", 1);
		close(STDIN_FILENO);
	}
}

//Modes: 1 = expand || 0 = pas expand
int	doing_here_doc_util(t_program *program, t_parser *lineread, char *tempfile, int mode)
{
	int					fd;
	char				*line;
	struct sigaction	act;
	int					stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler_heredoc;
	sigaction(SIGINT, &act, NULL);
	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (close(stdin_backup), perror("here_doc: open"), -1);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			program->last_exit_status = 130;
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			if (line)
				free(line);
			close(fd);
			return (1);
		}
		if (!line)
		{
			write(2, "\n", 1);
			ft_printf_fd(2, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", lineread->next->s);
			break ;
		}
		else if ((ft_strlen(line) == ft_strlen(lineread->next->s)
				&& !ft_strncmp(line, lineread->next->s,
					ft_strlen(lineread->next->s) + 1)))
		{
			free(line);
			break ;
		}
		if (mode == 1)
			line = expand_line(program, line, lineread);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(stdin_backup);
	close(fd);
	return (0);
}

int	doing_here_doc(t_program *program, char *tempfile)
{
	t_parser	*temp;
	int			mode;
	char 		*str;

	temp = *program->parsed;
	mode = 1;
	while (temp)
	{
		if (temp->type == DELIMITER)
		{
			if (ft_strchr(temp->next->s, '"') || ft_strchr(temp->next->s, '\''))
				mode = 0;
			if (ft_strchr(temp->next->s, '"'))
			{
				str = ft_strtrim(temp->next->s, "\"");
				if (!str)
					return (perror("here_doc: strtrim"), 1);
				free(temp->next->s);
				temp->next->s = str;
			}
			if (ft_strchr(temp->next->s, '\''))
			{
				str = ft_strtrim(temp->next->s, "'");
				if (!str)
					return (perror("here_doc: strtrim"), 1);
				free(temp->next->s);
				temp->next->s = str;
			}
			if (doing_here_doc_util(program, temp, tempfile, mode) == 1)
				return (1);
		}
		mode = 1;
		temp = temp->next;
	}
	return (0);
}
