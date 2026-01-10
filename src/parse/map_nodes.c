/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:57:10 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	add_node(t_map **map, t_map *new)
{
	t_map	*temp;

	if (!*map)
	{
		*map = new;
		return ;
	}
	temp = *map;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_map	*new_node(char *row)
{
	t_map	*new;

	new = ft_malloc(sizeof(t_map));
	if (row[ft_strlen(row) - 1] == '\n')
	{
		new->row = ft_malloc(sizeof(char) * ft_strlen(row));
		ft_strlcpy(new->row, row, ft_strlen(row));
	}
	else
		new->row = row;
	new->next = NULL;
	return (new);
}
