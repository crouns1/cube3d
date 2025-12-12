/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by yabarhda          #+#    #+#             */
/*   Updated: 2025/08/31 19:13:08 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	final_check(t_data *data, int fd)
{
	if (!data->texture->north || !data->texture->west || !data->texture->east \
		|| !data->texture->south || !data->texture->floor \
		|| !data->texture->ceiling)
	{
		ft_malloc(-42);
		ft_perror("Invalid texture file");
		close(fd);
		exit(1);
	}
}

static void	check_texture_file(t_data *data, int f)
{
	int	fd;

	fd = open(data->texture->north, O_RDONLY);
	if (fd == -1)
		(ft_malloc(-42), ft_perror("Invalid texture file"), close(f), exit(1));
	close(fd);
	fd = open(data->texture->west, O_RDONLY);
	if (fd == -1)
		(ft_malloc(-42), ft_perror("Invalid texture file"), close(f), exit(1));
	close(fd);
	fd = open(data->texture->south, O_RDONLY);
	if (fd == -1)
		(ft_malloc(-42), ft_perror("Invalid texture file"), close(f), exit(1));
	close(fd);
	fd = open(data->texture->east, O_RDONLY);
	if (fd == -1)
		(ft_malloc(-42), ft_perror("Invalid texture file"), close(f), exit(1));
	close(fd);
}

static int	validate_elements(t_data *data)
{
	if (!data->texture->north || !data->texture->west || !data->texture->east \
		|| !data->texture->south || !data->texture->floor \
		|| !data->texture->ceiling)
	{
		return (0);
	}
	return (1);
}

int	parse_file(t_data *data, char *file)
{
	int		fd;
	char	*line;
	char	**arr_line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		(ft_malloc(-42), close(fd), ft_perror("Empty file"), exit(1));
	while (line)
	{
		arr_line = ft_split(line, ' ');
		if (arr_line[0][0] == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		check_element(data, arr_line, fd);
		if (validate_elements(data))
			break ;
		line = get_next_line(fd);
	}
	final_check(data, fd);
	check_texture_file(data, fd);
	map_check(data, fd);
	return (1);
}
