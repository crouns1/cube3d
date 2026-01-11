/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 02:29:35 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	fill_draw_data(t_data *data, t_draw *draw)
{
	double	perp;

	if (data->ray.side == 0)
		draw->distance = data->ray.side_x - data->ray.delta_x;
	else
		draw->distance = data->ray.side_y - data->ray.delta_y;
	perp = draw->distance * cos(data->ray.angle - data->player.angle);
	if (perp < 0.0001)
		perp = 0.0001;
	draw->wall_h = HEIGHT / perp;
	set_draw_limits(draw->wall_h, &draw->start, &draw->end);
	draw->tex = get_hit_texture(data);
	draw->tex_x = get_texture_x(data, draw->tex, draw->distance);
	draw->step = (double)draw->tex->height / draw->wall_h;
	draw->tex_pos = (draw->start - HEIGHT / 2 + draw->wall_h / 2)
		* draw->step;
	draw->y = draw->start;
}
