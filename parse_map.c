/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:05:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/09 17:14:34 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

int	is_map_line(char *line)
{
	int	i;

	line = skip_spaces(line);
	if (!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3)
		|| !strncmp(line, "WE ", 3) || !strncmp(line, "EA ", 3)
		|| (!strncmp(line, "F", 1) && (line[1] == ' ' || line[1] == '\0'))
		|| (!strncmp(line, "C", 1) && (line[1] == ' ' || line[1] == '\0')))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (*line != '\0');
}

static int	set_player(t_data *data, int x, int y, char c)
{
	if (data->player_dir)
		return (err("Multiple players"), 1);
	data->player_x = x;
	data->player_y = y;
	data->player_dir = c;
	data->map[y][x] = '0';
	return (0);
}

static int	check_cell(t_data *data, int x, int y)
{
	char	c;

	c = data->map[y][x];
	if (c == '0')
	{
		if (x == 0 || y == 0 || x == data->map_width - 1
			|| y == data->map_height - 1)
			return (err("Map not closed"), 1);
		if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
			|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
			return (err("Map not closed"), 1);
	}
	return (0);
}

static int	process_char(t_data *data, int x, int y)
{
	char	c;

	c = data->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (set_player(data, x, y, c));
	if (c != '0' && c != '1' && c != ' ')
		return (err("Invalid map char"), 1);
	return (0);
}

static int	validate_row(t_data *data, int y)
{
	int	x;

	x = 0;
	while (x < data->map_width)
	{
		if (process_char(data, x, y))
			return (1);
		if (check_cell(data, x, y))
			return (1);
		x++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		if (validate_row(data, y))
			return (1);
		y++;
	}
	if (!data->player_dir)
		return (err("Missing player"), 1);
	return (0);
}

static int	copy_map_line(char *dst, char *src, int maxw)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(src);
	while (i < maxw)
	{
		if (i < len)
			dst[i] = src[i];
		else
			dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (0);
}

static int	calc_map_width(char **lines, int start)
{
	int	maxw;
	int	y;

	y = start;
	maxw = 0;
	while (lines[y])
	{
		if ((int)strlen(lines[y]) > maxw)
			maxw = strlen(lines[y]);
		y++;
	}
	return (maxw);
}

static int	alloc_rows(t_data *data, char **lines, int start)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = ft_malloc(data->map_width + 1);
		if (!data->map[i])
			return (err("Allocation failed"), 1);
		copy_map_line(data->map[i], lines[start + i], data->map_width);
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

int	build_map(t_data *data, char **lines, int start)
{
	int	y;

	data->map_width = calc_map_width(lines, start);
	y = start;
	while (lines[y])
		y++;
	data->map_height = y - start;
	data->map = ft_malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (err("Allocation failed"), 1);
	if (alloc_rows(data, lines, start))
		return (1);
	return (0);
}
