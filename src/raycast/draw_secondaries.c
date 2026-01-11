/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_secondaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:28:49 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 02:23:58 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

int	is_wall(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / BLOCK;
	map_y = y / BLOCK;
	if (data->map_array[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	clear_window(t_data *data)
{
	int	i;

	i = 0;
	while (i < (HEIGHT * data->size_line))
		data->img_addr[i++] = 0;
}

static int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_floor_ceiling(t_data *data)
{
	int	c_color;
	int	f_color;
	int	x;
	int	y;

	c_color = get_rgb(data->texture->ceiling[0], data->texture->ceiling[1], \
		data->texture->ceiling[2]);
	f_color = get_rgb(data->texture->floor[0], data->texture->floor[1], \
		data->texture->floor[2]);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(data, x, y, c_color);
			else
				put_pixel(data, x, y, f_color);
			x++;
		}
		y++;
	}
}
