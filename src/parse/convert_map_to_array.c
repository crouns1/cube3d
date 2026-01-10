/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:56:37 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	convert_map_to_array(t_data *data)
{
	t_map	*current;
	int		i;

	current = data->map;
	while (current)
	{
		data->map_height++;
		if (ft_strlen(current->row) > (size_t)data->map_width)
			data->map_width = ft_strlen(current->row);
		current = current->next;
	}
	data->map_array = ft_malloc(sizeof(char *) * (data->map_height + 1));
	current = data->map;
	i = 0;
	while (current)
	{
		data->map_array[i++] = current->row;
		current = current->next;
	}
	data->map_array[i] = NULL;
}
