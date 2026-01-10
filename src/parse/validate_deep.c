/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_deep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:57:33 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static char	**alloc_map_copy(int size)
{
	char	**map;

	map = ft_malloc(sizeof(char *) * (size + 1));
	map[size] = NULL;
	return (map);
}

static void	fill_map_copy(t_data *data, char **map)
{
	t_map	*tmp;
	int		i;

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
}

void	deep_check(t_data *data)
{
	char	**map;

	map = alloc_map_copy(data->map->size);
	fill_map_copy(data, map);
	check_borders(map);
}
