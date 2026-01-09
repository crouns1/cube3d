/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:45:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/09 17:14:40 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

static int	ensure_capacity(char ***lines, int size, int *cap)
{
	char	**new_arr;
	int		i;
	int		new_cap;

	if (size + 1 < *cap)
		return (0);
	
	if (*cap == 0)
		new_cap = 16;
	else
		new_cap = *cap * 2;

	new_arr = ft_malloc(sizeof(char *) * new_cap);
	if (!new_arr)
		return (err("Allocation failed"), 1);
	i = 0;
	while (i < size)
	{
		if (*lines)
			new_arr[i] = (*lines)[i];
		else
			new_arr[i] = NULL;
		i++;
	}
	ft_free(*lines);
	*lines = new_arr;
	*cap = new_cap;
	return (0);
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

char	**read_lines(const char *path)
{
	int		(fd)  , (size) , (cap);
	char		*line;
	char		**lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err("Read failed"), NULL);
	lines = NULL;
	size = 0;
	cap = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ensure_capacity(&lines, size, &cap))
			return (close(fd), ft_free(line), free_lines(lines), NULL);
		if (strlen(line) > 0 && line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		lines[size++] = line;
		line = get_next_line(fd);
	}
	close(fd);
	if (ensure_capacity(&lines, size, &cap))
		return (free_lines(lines), NULL);
	lines[size] = NULL;
	return (lines);
}

char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}
