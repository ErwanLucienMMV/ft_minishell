/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:11:34 by abarthes          #+#    #+#             */
/*   Updated: 2025/12/28 14:42:50 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_is_newline(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	if (buffer[i] == '\n')
		return (1);
	return (0);
}

char	*ft_get_line(char *buffer)
{
	int		n;
	int		i;
	char	*line;

	i = 0;
	n = ft_get_newline(buffer) + 1;
	line = ft_calloc((n + 1), sizeof(char));
	if (!line)
		return (0);
	while (i < n)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*ft_clear_buffer(char *str, int n)
{
	int		i;
	int		size;
	char	*temp;

	size = n + 1;
	temp = ft_calloc((ft_strlen(str + size) + 1), sizeof(char));
	if (!temp)
		return (0);
	i = 0;
	while (str[i + size])
	{
		temp[i] = str[i + size];
		i++;
	}
	temp[i] = 0;
	free(str);
	return (temp);
}

char	*ft_get_buffer(int fd, char *buffer)
{
	int		ret;
	char	*stash;

	ret = 1;
	stash = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (ret != 0 && !ft_is_newline(buffer))
	{
		ret = read(fd, stash, BUFFER_SIZE);
		if (ret < 0)
		{
			free(buffer);
			free(stash);
			return (0);
		}
		if (ret)
		{
			stash[ret] = 0;
			buffer = ft_strjoin_gnl(buffer, stash);
		}
	}
	free(stash);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_get_buffer(fd, buffer);
	if (!buffer || !buffer[0])
	{
		free(buffer);
		buffer = NULL;
		return (0);
	}
	line = ft_get_line(buffer);
	buffer = ft_clear_buffer(buffer, ft_get_newline(buffer));
	if (!buffer)
		return (0);
	return (line);
}

// int main(void)
// {
// 	#include <stdio.h>
// 	#include <fcntl.h>
// 	int fd = open("test.txt", O_RDONLY);
// 	while(1)
// 	{
// 		char *temp = get_next_line(fd);
// 		if(temp == NULL)
// 		{
// 			free(temp);
// 			return 1;
// 		}
// 		else
// 		{
// 			printf("%s", temp);
// 			free(temp);
// 		}
// 	}
// 	return 0;
// }