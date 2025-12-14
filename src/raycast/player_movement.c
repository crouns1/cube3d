/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:43:46 by yabarhda          #+#    #+#             */
/*   Updated: 2025/12/14 10:21:41 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

int	on_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		clean_exit(data);
	if (key == KEY_RIGHT)
		data->player.key_right = true;
	if (key == KEY_LEFT)
		data->player.key_left = true;
	if (key == KEY_W)
		data->player.key_w = true;
	if (key == KEY_A)
		data->player.key_a = true;
	if (key == KEY_S)
		data->player.key_s = true;
	if (key == KEY_D)
		data->player.key_d = true;
	return (0);
}

int	on_keyrelease(int key, t_data *data)
{
	if (key == KEY_RIGHT)
		data->player.key_right = false;
	if (key == KEY_LEFT)
		data->player.key_left = false;
	if (key == KEY_W)
		data->player.key_w = false;
	if (key == KEY_A)
		data->player.key_a = false;
	if (key == KEY_S)
		data->player.key_s = false;
	if (key == KEY_D)
		data->player.key_d = false;
	return (0);
}

// void	move_player(t_data *data)
// {
// 	if (data->player.key_right)
// 		printf("right arrow\n");
// 	if (data->player.key_left)
// 		printf("left arrow\n");
// 	if (data->player.key_w)
// 		printf("w key\n");
// 	if (data->player.key_a)
// 		printf("a key\n");
// 	if (data->player.key_s)
// 		printf("s key\n");
// 	if (data->player.key_d)
// 		printf("d key\n");
// }

void	move_player(t_data *data)
{
    double move_speed = 0.1;
    double rot_speed = 0.05;
    double old_dir_x, old_plane_x;

    // Forward
    if (data->player.key_w)
    {
        if (data->map_array[(int)(data->player.y)][(int)(data->player.x + data->player.dir_x * move_speed)] == '0')
            data->player.x += data->player.dir_x * move_speed;
        if (data->map_array[(int)(data->player.y + data->player.dir_y * move_speed)][(int)(data->player.x)] == '0')
            data->player.y += data->player.dir_y * move_speed;
    }
    // Backward
    if (data->player.key_s)
    {
        if (data->map_array[(int)(data->player.y)][(int)(data->player.x - data->player.dir_x * move_speed)] == '0')
            data->player.x -= data->player.dir_x * move_speed;
        if (data->map_array[(int)(data->player.y - data->player.dir_y * move_speed)][(int)(data->player.x)] == '0')
            data->player.y -= data->player.dir_y * move_speed;
    }
    // Left
    if (data->player.key_a)
    {
        if (data->map_array[(int)(data->player.y)][(int)(data->player.x - data->player.plane_x * move_speed)] == '0')
            data->player.x -= data->player.plane_x * move_speed;
        if (data->map_array[(int)(data->player.y - data->player.plane_y * move_speed)][(int)(data->player.x)] == '0')
            data->player.y -= data->player.plane_y * move_speed;
    }
    // Right
    if (data->player.key_d)
    {
        if (data->map_array[(int)(data->player.y)][(int)(data->player.x + data->player.plane_x * move_speed)] == '0')
            data->player.x += data->player.plane_x * move_speed;
        if (data->map_array[(int)(data->player.y + data->player.plane_y * move_speed)][(int)(data->player.x)] == '0')
            data->player.y += data->player.plane_y * move_speed;
    }
    // Rotate right
    if (data->player.key_right)
    {
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
        data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
        data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
    }
    // Rotate left
    if (data->player.key_left)
    {
        old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
        data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
        old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
        data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
    }
}