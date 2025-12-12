/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:50:38 by yabarhda          #+#    #+#             */
/*   Updated: 2025/09/01 10:46:43 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	standard_check(t_data *data)
{
	int (x), y;
	t_map *(tmp);
	y = 0;
	tmp = data->map;
	while (tmp)
	{
		x = 0;
		while (tmp->row[x])
		{
			if (ft_isplayer(tmp->row[x]))
			{
				if (data->player.x)
					(ft_malloc(-42), ft_perror("Invalid map"), exit(1));
				data->player.x = x;
				data->player.y = y;
				data->player.direction = tmp->row[x];
				tmp->row[x] = '0';
			}
			x++;
		}
		y++;
		tmp = tmp->next;
	}
	if (!data->player.x)
		(ft_malloc(-42), ft_perror("Invalid map"), exit(1));
}

static void	dfs(t_data *data, char **map, int x, int y)
{
	if (x == 0 || y == 0 || y == data->map->size - 1 \
		|| x == (int)ft_strlen(map[y]) - 1)
	{
		if (map[y][x] != '1')
			(ft_malloc(-42), ft_perror("Invalid map"), exit(1));
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == ' ' || !map[y][x])
		(ft_malloc(-42), ft_perror("Invalid map"), exit(1));
	map[y][x] = 'F';
	dfs(data, map, x + 1, y);
	dfs(data, map, x - 1, y);
	dfs(data, map, x, y + 1);
	dfs(data, map, x, y - 1);
}

static void	deep_check(t_data *data)
{
	int		i;
	char	**map;
	t_map	*tmp;

	map = ft_malloc(sizeof(char *) * (data->map->size + 1));
	map[data->map->size] = NULL;
	tmp = data->map;
	i = 0;
	while (tmp)
	{
		map[i] = ft_strdup(tmp->row);
		if (!map[i][0])
			(ft_malloc(-42), ft_perror("Invalid map"), exit(1));
		tmp = tmp->next;
		i++;
	}
	dfs(data, map, data->player.x, data->player.y);
}

static void	get_map_size(t_data *data)
{
	t_map	*tmp;
	int		size;

	tmp = data->map;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	tmp = data->map;
	while (tmp)
	{
		tmp->size = size;
		tmp = tmp->next;
	}
}

void	validate_map(t_data *data)
{
	get_map_size(data);
	standard_check(data);
	deep_check(data);
}
