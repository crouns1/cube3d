/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:26:13 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/15 07:34:11 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int	check_collision(t_data *data, float new_x, float new_y)
{
	if (new_x >= 0 && new_x < data->map_width && new_y >= 0 && new_y < data->map_height
		&& data->map_array[(int)new_y][(int)new_x] != '1')
		return (1);
	return (0);
}

static void	move_forward(t_data *data, float move_speed)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.dir_x * move_speed;
	new_y = data->player.y + data->player.dir_y * move_speed;
	if (check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	move_backward(t_data *data, float move_speed)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.dir_x * move_speed;
	new_y = data->player.y - data->player.dir_y * move_speed;
	if (check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	move_left(t_data *data, float move_speed)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.plane_x * move_speed;
	new_y = data->player.y - data->player.plane_y * move_speed;
	if (check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	move_right(t_data *data, float move_speed)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.plane_x * move_speed;
	new_y = data->player.y + data->player.plane_y * move_speed;
	if (check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	handle_movement(t_data *data)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 0.01;
	rot_speed = 0.01;
	if (data->player.key_w)
		move_forward(data, move_speed);
	if (data->player.key_s)
		move_backward(data, move_speed);
	if (data->player.key_a)
		move_left(data, move_speed);
	if (data->player.key_d)
		move_right(data, move_speed);
	if (data->player.key_left)
		rotate_player(data, -rot_speed);
	if (data->player.key_right)
		rotate_player(data, rot_speed);
}

void	rotate_player(t_data *data, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle) - data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y * cos(angle);
}
