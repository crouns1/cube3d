/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:57:16 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int	elements_ready(t_data *data)
{
	if (!data->texture->north || !data->texture->west || !data->texture->east
		|| !data->texture->south || !data->texture->floor
		|| !data->texture->ceiling)
		return (0);
	return (1);
}

void	require_elements(t_data *data, int fd)
{
	if (!elements_ready(data))
	{
		ft_malloc(-42);
		ft_perror("Invalid map");
		close(fd);
		exit(1);
	}
}

void	parse_elements(t_data *data, int fd)
{
	char	*line;
	char	**arr;

	line = get_next_line(fd);
	if (!line)
		(ft_malloc(-42), close(fd), ft_perror("Empty file"), exit(1));
	while (line && !elements_ready(data))
	{
		arr = ft_split(line, ' ');
		if (!arr[0] || arr[0][0] == '\0' || arr[0][0] == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		check_element(data, arr, fd);
		line = get_next_line(fd);
	}
}
