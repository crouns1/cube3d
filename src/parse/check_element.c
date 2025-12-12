/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:18:58 by yabarhda          #+#    #+#             */
/*   Updated: 2025/08/31 19:00:21 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	assign_texture(char **arr, char **texture, int fd)
{
	if (*texture)
	{
		ft_malloc(-42);
		ft_perror("Multiple definitions of textures");
		close(fd);
		exit(1);
	}
	if (!arr[1] || arr[2])
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	if (arr[1][ft_strlen(arr[1]) - 1] == '\n')
	{
		*texture = ft_malloc(sizeof(char) * ft_strlen(arr[1]));
		ft_strlcpy(*texture, arr[1], ft_strlen(arr[1]));
	}
	else
		*texture = arr[1];
}

static int	value_check(char *s, int fd)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (ft_strlen(s) > 4)
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '\n')
			(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
		i++;
	}
	result = ft_atoi(s);
	if (result < 0 || result > 255)
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	return (result);
}

static void	assign_colors(char **arr, unsigned char **texture, int fd)
{
	int		i;
	char	**tmp_arr;

	if (*texture)
	{
		ft_malloc(-42);
		ft_perror("Multiple definitions of floor colors");
		close(fd);
		exit(1);
	}
	if (!arr[1])
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	tmp_arr = ft_split(arr[1], ',');
	i = 0;
	*texture = ft_malloc(sizeof(unsigned char) * 3);
	while (tmp_arr[i])
	{
		if (tmp_arr[i][0] == '\n' || i == 3)
			(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
		(*texture)[i] = value_check(tmp_arr[i], fd);
		i++;
	}
	if (i != 3)
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
}

void	check_element(t_data *data, char **arr, int fd)
{
	if (!ft_strcmp(arr[0], "NO"))
		assign_texture(arr, &data->texture->north, fd);
	else if (!ft_strcmp(arr[0], "SO"))
		assign_texture(arr, &data->texture->south, fd);
	else if (!ft_strcmp(arr[0], "WE"))
		assign_texture(arr, &data->texture->west, fd);
	else if (!ft_strcmp(arr[0], "EA"))
		assign_texture(arr, &data->texture->east, fd);
	else if (!ft_strcmp(arr[0], "F"))
		assign_colors(arr, &data->texture->floor, fd);
	else if (!ft_strcmp(arr[0], "C"))
		assign_colors(arr, &data->texture->ceiling, fd);
	else
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
}
