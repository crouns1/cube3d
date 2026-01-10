/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:09:24 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/10 02:04:19 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	init_ray_coords(t_data *data)
{
	data->ray.map_x = data->player.x / BLOCK;
	data->ray.map_y = data->player.y / BLOCK;
	data->ray.pos_x = data->player.x / BLOCK;
	data->ray.pos_y = data->player.y / BLOCK;
	data->ray.delta_x = fabs(1 / cos(data->ray.angle));
	data->ray.delta_y = fabs(1 / sin(data->ray.angle));
}

static void	init_ray_step(t_data *data)
{
	init_ray_coords(data);
	if (cos(data->ray.angle) < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_x = (data->ray.pos_x - data->ray.map_x) * \
		data->ray.delta_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_x = (data->ray.map_x + 1 - data->ray.pos_x) * \
		data->ray.delta_x;
	}
	if (sin(data->ray.angle) < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_y = (data->ray.pos_y - data->ray.map_y) * \
		data->ray.delta_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_y = (data->ray.map_y + 1 - data->ray.pos_y) * \
		data->ray.delta_y;
	}
}

static void	dda(t_data *data)
{
	while (data->map_array[data->ray.map_y][data->ray.map_x] != '1')
	{
		if (data->ray.side_x < data->ray.side_y)
		{
			data->ray.side_x += data->ray.delta_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_y += data->ray.delta_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
	}
}

static void	draw_texture(t_data *data, int x)
{
	t_draw	draw;

	fill_draw_data(data, &draw);
	while (draw.y < draw.end)
	{
		put_pixel(data, x, draw.y, get_texture_color(draw.tex, draw.tex_x, \
			(int)draw.tex_pos));
		draw.tex_pos += draw.step;
		draw.y++;
	}
}

void	draw_rays(t_data *data)
{
	static bool	textured;
	float		step;
	float		offset;
	int			x;

	if (!textured)
	{
		init_textures(data);
		textured = true;
	}
	offset = (FOV / 2) * (PI / 180);
	data->ray.angle = data->player.angle - offset;
	step = (FOV * (PI / 180)) / WIDTH;
	x = 0;
	while (x < WIDTH)
	{
		init_ray_step(data);
		dda(data);
		draw_texture(data, x);
		data->ray.angle += step;
		x++;
	}
}
