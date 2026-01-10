/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:21:32 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 12:02:20 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static char	*skip_empty_lines(int fd, char *line)
{
	while (line && only_spaces(line))
		line = get_next_line(fd);
	return (line);
}

static void	drain_after_gap(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!only_spaces(line))
			(ft_malloc(-42), close(fd), ft_perror("Invalid map"), exit(1));
		line = get_next_line(fd);
	}
}

static void	validate_and_add(t_data *data, int fd, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && !valid_map_char(line[i]))
			(ft_malloc(-42), close(fd), ft_perror("Invalid map"), exit(1));
		i++;
	}
	add_node(&data->map, new_node(line));
}

void	map_check(t_data *data, int fd)
{
	char	*line;

	line = skip_empty_lines(fd, get_next_line(fd));
	while (line)
	{
		if (only_spaces(line))
		{
			drain_after_gap(fd);
			break ;
		}
		validate_and_add(data, fd, line);
		line = get_next_line(fd);
	}
	close(fd);
	validate_map(data);
}
