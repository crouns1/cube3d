/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:22:36 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 02:23:58 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

int	on_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		clean_exit(data);
	if (key == KEY_W)
		data->player.key_w = true;
	if (key == KEY_A)
		data->player.key_a = true;
	if (key == KEY_S)
		data->player.key_s = true;
	if (key == KEY_D)
		data->player.key_d = true;
	if (key == KEY_RIGHT)
		data->player.key_right = true;
	if (key == KEY_LEFT)
		data->player.key_left = true;
	return (0);
}

int	on_keyrelease(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.key_w = false;
	if (key == KEY_A)
		data->player.key_a = false;
	if (key == KEY_S)
		data->player.key_s = false;
	if (key == KEY_D)
		data->player.key_d = false;
	if (key == KEY_RIGHT)
		data->player.key_right = false;
	if (key == KEY_LEFT)
		data->player.key_left = false;
	return (0);
}

static void	try_step(t_data *data, double angle, int dir)
{
	double	new_x;
	double	new_y;
	double	cush_x;
	double	cush_y;

	new_x = data->player.x + (dir * MOVE_SPEED * cos(angle));
	new_y = data->player.y + (dir * MOVE_SPEED * sin(angle));
	cush_x = new_x + (dir * 7 * cos(angle));
	cush_y = new_y + (dir * 7 * sin(angle));
	if (!is_wall(data, cush_x, cush_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	rotate_player(t_data *data)
{
	if (data->player.key_left)
	{
		data->player.angle -= 0.025;
		if (data->player.angle <= 0)
			data->player.angle += 2 * PI;
	}
	if (data->player.key_right)
	{
		data->player.angle += 0.025;
		if (data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
	}
}

void	move_player(t_data *data)
{
	if (data->player.key_w)
		try_step(data, data->player.angle, 1);
	if (data->player.key_s)
		try_step(data, data->player.angle, -1);
	if (data->player.key_a)
		try_step(data, data->player.angle + (PI / 2), -1);
	if (data->player.key_d)
		try_step(data, data->player.angle + (PI / 2), 1);
	rotate_player(data);
}
