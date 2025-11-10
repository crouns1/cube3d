/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:14:20 by yabarhda          #+#    #+#             */
/*   Updated: 2025/09/11 17:00:45 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int	check_newline(char *string)
{
	if (!string)
		return (0);
	while (*string)
	{
		if (*string == '\n')
			return (1);
		string++;
	}
	return (0);
}

static char	*extract_line(char **stash)
{
	int		line_len;
	int		is_newline;
	char	*line;
	char	*temp_stash;

	line_len = 0;
	is_newline = 0;
	temp_stash = NULL;
	while ((*stash)[line_len] != '\n' && (*stash)[line_len] != '\0')
		line_len++;
	if ((*stash)[line_len] == '\n')
		is_newline = 1;
	line = ft_malloc(line_len + is_newline + 1);
	ft_strlcpy(line, *stash, line_len + is_newline + 1);
	if ((*stash)[line_len] == '\n')
		temp_stash = ft_strdup(*stash + line_len + 1);
	*stash = NULL;
	if (temp_stash)
		*stash = ft_strdup(temp_stash);
	return (line);
}

static int	extract_and_stash(int fd, char **stash, char *buffer)
{
	int		size;
	char	*temp;

	size = read(fd, buffer, 1);
	if (size < 0)
		return (-1);
	buffer[size] = '\0';
	if (!*stash)
		*stash = ft_strdup(buffer);
	else
	{
		temp = *stash;
		*stash = ft_strjoin(*stash, buffer);
	}
	return (size);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			size;

	buffer = NULL;
	if (1 <= 0 || fd <= -1)
		return (NULL);
	buffer = ft_malloc(sizeof(char) * (1 + 1));
	size = 1;
	while (check_newline(stash) == 0 && size > 0)
	{
		size = extract_and_stash(fd, &stash, buffer);
		if (size < 0 || stash[0] == '\0')
		{
			stash = NULL;
			return (NULL);
		}			
	}
	return (extract_line(&stash));
}
