/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:05:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 11:31:11 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

int	is_map_line(char *line)
{
	int	idx;

	line = skip_spaces(line);
	if (!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3)
		|| !strncmp(line, "WE ", 3) || !strncmp(line, "EA ", 3)
		|| (!strncmp(line, "F", 1) && (line[1] == ' ' || line[1] == '\0'))
		|| (!strncmp(line, "C", 1) && (line[1] == ' ' || line[1] == '\0')))
		return (0);
	idx = 0;
	while (line[idx])
	{
		if (line[idx] != ' ' && line[idx] != '0' && line[idx] != '1'
			&& line[idx] != 'N' && line[idx] != 'S'
			&& line[idx] != 'E' && line[idx] != 'W')
			return (0);
		idx++;
	}
	return (*line != '\0');
}

static int	set_player(t_data *d, int x, int y, char c)
{
	if (d->player_dir)
		return (err("Multiple players"), 1);
	d->player_x = x;
	d->player_y = y;
	d->player_dir = c;
	d->map[y][x] = '0';
	return (0);
}

static int	check_cell(t_data *d, int x, int y)
{
	char	c;

	c = d->map[y][x];
	if (c == '0')
	{
		if (x == 0 || y == 0 || x == d->map_width - 1
			|| y == d->map_height - 1)
			return (err("Map not closed"), 1);
		if (d->map[y - 1][x] == ' ' || d->map[y + 1][x] == ' '
			|| d->map[y][x - 1] == ' ' || d->map[y][x + 1] == ' ')
			return (err("Map not closed"), 1);
	}
	return (0);
}

static int	process_char(t_data *d, int x, int y)
{
	char	c;

	c = d->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (set_player(d, x, y, c));
	if (c != '0' && c != '1' && c != ' ')
		return (err("Invalid map char"), 1);
	return (0);
}

static int	validate_row(t_data *d, int y)
{
	int	x;

	x = 0;
	while (x < d->map_width)
	{
		if (process_char(d, x, y))
			return (1);
		if (check_cell(d, x, y))
			return (1);
		x++;
	}
	return (0);
}

int	validate_map(t_data *d)
{
	int	y;

	y = 0;
	while (y < d->map_height)
	{
		if (validate_row(d, y))
			return (1);
		y++;
	}
	if (!d->player_dir)
		return (err("Missing player"), 1);
	return (0);
}

static int	copy_map_line(char *dst, char *src, int maxw)
{
	int	idx;
	int	len;

	idx = 0;
	len = strlen(src);
	while (idx < maxw)
	{
		if (idx < len)
			dst[idx] = src[idx];
		else
			dst[idx] = ' ';
		idx++;
	}
	dst[idx] = '\0';
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

static int	alloc_rows(t_data *d, char **lines, int start)
{
	int	idx;

	idx = 0;
	while (idx < d->map_height)
	{
		d->map[idx] = ft_malloc(d->map_width + 1);
		if (!d->map[idx])
			return (err("Allocation failed"), 1);
		copy_map_line(d->map[idx], lines[start + idx], d->map_width);
		idx++;
	}
	d->map[idx] = NULL;
	return (0);
}

int	build_map(t_data *d, char **lines, int start)
{
	int	y;

	d->map_width = calc_map_width(lines, start);
	y = start;
	while (lines[y])
		y++;
	d->map_height = y - start;
	d->map = ft_malloc(sizeof(char *) * (d->map_height + 1));
	if (!d->map)
		return (err("Allocation failed"), 1);
	if (alloc_rows(d, lines, start))
		return (1);
	return (0);
}
