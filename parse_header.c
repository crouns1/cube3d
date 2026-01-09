/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:00:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/09 17:14:32 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

int	set_texture(char **dst, char *line)
{
	if (*dst)
		return (err("Duplicate texture"), 1);
	line = skip_spaces(line);
	if (!*line)
		return (err("Empty texture path"), 1);
	*dst = ft_malloc(strlen(line) + 1);
	if (!*dst)
		return (err("Allocation failed"), 1);
	strcpy(*dst, line);
	return (0);
}

static int	parse_one_value(char **ptr)
{
	int	value;

	value = 0;
	if (**ptr < '0' || **ptr > '9')
		return (-1);
	while (**ptr >= '0' && **ptr <= '9')
	{
		value = value * 10 + (**ptr - '0');
		(*ptr)++;
	}
	return (value);
}

static int	store_component(int out[3], int *idx, char **line)
{
	int	val;

	val = parse_one_value(line);
	if (val < 0 || val > 255)
		return (err("Invalid color"), 1);
	out[*idx] = val;
	(*idx)++;
	*line = skip_spaces(*line);
	return (0);
}

int	parse_color(int out[3], char *line)
{
	int	idx;

	idx = 0;
	line = skip_spaces(line);
	while (idx < 3)
	{
		if (store_component(out, &idx, &line))
			return (1);
		if (idx < 3)
		{
			if (*line != ',')
				return (err("Color format"), 1);
			line = skip_spaces(line + 1);
		}
	}
	if (*line)
		return (err("Trailing color data"), 1);
	return (0);
}

int	parse_header_line(t_data *data, char *line)
{
	line = skip_spaces(line);
	if (!strncmp(line, "NO", 2) && line[2] == ' ')
		return (set_texture(&data->tex_no, line + 3));
	if (!strncmp(line, "SO", 2) && line[2] == ' ')
		return (set_texture(&data->tex_so, line + 3));
	if (!strncmp(line, "WE", 2) && line[2] == ' ')
		return (set_texture(&data->tex_we, line + 3));
	if (!strncmp(line, "EA", 2) && line[2] == ' ')
		return (set_texture(&data->tex_ea, line + 3));
	if (*line == 'F' && line[1] == ' ')
		return (parse_color(data->floor, line + 2));
	if (*line == 'C' && line[1] == ' ')
		return (parse_color(data->ceiling, line + 2));
	if (*line == '\0')
		return (0);
	return (err("Unknown identifier"), 1);
}
