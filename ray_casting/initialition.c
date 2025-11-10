/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:56:34 by jait-chd          #+#    #+#             */
/*   Updated: 2025/11/10 10:58:30 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"


void init_mlx(t_data *data) {
    data->mlx = NULL;
	data->map = NULL;
	data->img = NULL;
	data->img_addr = NULL;
	data->size_line = 0;
	data->bpp = 0;
	data->endien = 0;
}


void init_player(t_data *data) {

    data->player.x = 0;
	data->player.y = 0;
	data->player.angle = 0;
	data->player.direction = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
}
