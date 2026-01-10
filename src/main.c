/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:59:43 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/10 07:26:20 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	error_check(int ac, char **av)
{
	int	fd;
	int	len;

	if (ac != 2)
		return (printf("Error\nNot enough arguments\n"), 0);
	len = ft_strlen(av[1]);
	if (ft_strcmp(".cub", &av[1][len - 4]))
		return (printf("Error\nInvalid file format\n"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nNo such file or directory\n"), 0);
	close(fd);
	return (1);
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
	data->texture = ft_malloc(sizeof(t_texture));
	data->texture->north = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	data->texture->east = NULL;
	data->texture->floor = NULL;
	data->texture->ceiling = NULL;
	data->player.x = 0;
	data->player.y = 0;
	data->player.angle = 0;
	data->player.direction = 0;
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

void	init_player(t_data *data)
{
	data->player.key_w = false;
	data->player.key_a = false;
	data->player.key_s = false;
	data->player.key_d = false;
	data->player.key_right = false;
	data->player.key_left = false;
	if (data->player.direction == 'N')
		data->player.angle = 3 * PI / 2;
	else if (data->player.direction == 'S')
		data->player.angle = PI / 2;
	else if (data->player.direction == 'E')
		data->player.angle = 0;
	else if (data->player.direction == 'W')
		data->player.angle = PI;
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
	init_cub(data);
	return (0);
}
