/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:00:11 by jait-chd          #+#    #+#             */
/*   Updated: 2025/09/08 20:00:38 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"


void	convert_map_to_array(t_data *data)
{
	t_map	*tmp;
	int		i;

	data->map_height = 0;
	tmp = data->map;
	while (tmp)
	{
		data->map_height++;
		tmp = tmp->next;
	}
	data->map_width = ft_strlen(data->map->row);
	data->map_array = ft_malloc(sizeof(char *) * (data->map_height + 1));
	data->map_array[data->map_height] = NULL;
	tmp = data->map;
	i = 0;
	while (tmp)
	{
		data->map_array[i] = ft_strdup(tmp->row);
		tmp = tmp->next;
		i++;
	}
}
