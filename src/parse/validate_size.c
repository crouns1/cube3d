/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 12:08:59 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	get_map_size(t_data *data)
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
