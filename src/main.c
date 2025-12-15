/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:59:43 by yabarhda          #+#    #+#             */
/*   Updated: 2025/12/15 10:02:38 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	error_check(int ac, char **av)
{
	int	fd;
	int	len;

	if (ac != 2)
		return (printf("Error\nNot enough arguments\n"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nNo such file or directory\n"), 0);
	close(fd);
	len = ft_strlen(av[1]);
	if (ft_strcmp(".cub", &av[1][len - 4]))
		return (printf("Error\nInvalid file format\n"), 0);
	return (1);
}
static void init_textures(t_data *data)
{
	data->texture = ft_malloc(sizeof(t_texture));
	data->texture->north = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	data->texture->east = NULL;
	data->texture->floor = NULL;
	data->texture->ceiling = NULL;
}
static void init_player_info(t_data *data) {
	data->player.x = 0;
	data->player.y = 0;
	data->player.angle = 0;
	data->player.direction = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.key_w = false;
	data->player.key_a = false;
	data->player.key_s = false;
	data->player.key_d = false;
	data->player.key_right = false;
	data->player.key_left = false;
}
static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->map = NULL;
	data->img = NULL;
	data->img_addr = NULL;
	data->size_line = 0;
	data->bpp = 0;
	data->endien = 0;
	data->width = WIDTH;
	data->height = HEIGHT;
	data->map_array = NULL;
	data->map_width = 0;
	data->map_height = 0;
	init_textures(data);
	init_player_info(data);
	
}

int	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_malloc(-42);
	exit(0);
}

int	render(t_data *data)
{
	raycast(data);
	handle_movement(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	key_hooks(int key, t_data *data)
{
	if (key == KEY_ESC)
		clean_exit(data);
	return (0);
}

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

int	main(int ac, char **av)
{
	t_data	*data;

	if (!error_check(ac, av))
		return (1);
	data = ft_malloc(sizeof(t_data));
	init_data(data);
	parse_file(data, av[1]);
	init_player(data);
	convert_map_to_array(data);
	data->mlx = mlx_init();
	load_textures(data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_addr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endien);
	mlx_hook(data->win, 17, 1L << 0, clean_exit, data);
	mlx_hook(data->win, 2, 1L << 0, on_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, on_keyrelease, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	return (0);
}
