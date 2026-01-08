/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:45:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 09:45:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

static int	append_chunk(char **content, size_t *len, char *buf, ssize_t r)
{
	char	*newc;

	newc = ft_malloc(*len + r + 1);
	if (!newc)
		return (1);
	if (*content)
		memcpy(newc, *content, *len);
	memcpy(newc + *len, buf, r);
	ft_free(*content);
	*len += r;
	newc[*len] = '\0';
	*content = newc;
	return (0);
}

static int	read_chunks(int fd, char **content, size_t *len)
{
	char	buf[1024];
	ssize_t	r;

	r = read(fd, buf, 1024);
	while (r > 0)
	{
		if (append_chunk(content, len, buf, r))
			return (1);
		r = read(fd, buf, 1024);
	}
	return (r < 0);
}

char	*read_file_content(const char *path)
{
	int		fd;
	char	*content;
	size_t	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = NULL;
	len = 0;
	if (read_chunks(fd, &content, &len))
		return (close(fd), ft_free(content), NULL);
	close(fd);
	return (content);
}

static char	*substr_dup(char *s, int len)
{
	char	*out;
	int		i;

	out = ft_malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = s[i];
		i++;
	}
	out[len] = '\0';
	return (out);
}

static int	count_lines(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && s[i - 1] != '\n')
		count++;
	return (count);
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		ft_free(lines[i]);
		i++;
	}
	ft_free(lines);
}

static int	push_line(char **out, int *line_i, char *start, int len)
{
	out[*line_i] = substr_dup(start, len);
	if (!out[*line_i])
		return (1);
	(*line_i)++;
	return (0);
}

static int	fill_lines(char **out, char *content)
{
	int	i;
	int	start;
	int	line_i;

	i = 0;
	start = 0;
	line_i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			if (push_line(out, &line_i, content + start, i - start))
				return (-1);
			start = i + 1;
		}
		i++;
	}
	if (i != start && push_line(out, &line_i, content + start, i - start))
		return (-1);
	out[line_i] = NULL;
	return (0);
}

char	**split_lines(char *content)
{
	int		lines_cnt;
	char	**out;

	if (!content)
		return (NULL);
	lines_cnt = count_lines(content);
	out = ft_malloc(sizeof(char *) * (lines_cnt + 1));
	if (!out)
		return (NULL);
	if (fill_lines(out, content) < 0)
		return (free_lines(out), NULL);
	return (out);
}

char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}
