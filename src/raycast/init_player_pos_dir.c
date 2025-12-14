/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_pos_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:26:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/14 09:08:36 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"


void	init_player_direction(t_data *data)
{
	if (data->player.direction == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0;
	}
	else if (data->player.direction == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0;
	}
	else if (data->player.direction == 'E')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0;
	}
	else if (data->player.direction == 'W')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0;
	}
}

void	init_player(t_data *data)
{
	if (data->player.direction == 'N')
		data->player.angle = 0;
	else if (data->player.direction == 'E')
		data->player.angle = 90;
	else if (data->player.direction == 'S')
		data->player.angle = 180;
	else if (data->player.direction == 'W')
		data->player.angle = 270;
	init_player_direction(data);
}