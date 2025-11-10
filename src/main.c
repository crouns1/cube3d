/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:59:43 by yabarhda          #+#    #+#             */
/*   Updated: 2025/11/10 11:00:38 by jait-chd         ###   ########.fr       */
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
	len = ft_strlen(av[1]);
	if (ft_strcmp(".cub", &av[1][len - 4]))
		return (printf("Error\nInvalid file format\n"), close(fd), 0);
	return (1);
}

static void	init_data(t_data *data)
{
	// data->mlx = NULL;
	// data->map = NULL;
	// data->img = NULL;
	// data->img_addr = NULL;
	// data->size_line = 0;
	// data->bpp = 0;
	// data->endien = 0;
	data->width = WIDTH;
	data->height = HEIGHT;
	data->map_array = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->texture = ft_malloc(sizeof(t_texture));
	// data->texture->north = NULL;
	// data->texture->south = NULL;
	// data->texture->west = NULL;
	// data->texture->east = NULL;
	// data->texture->floor = NULL;
	// data->texture->ceiling = NULL;
	// data->player.x = 0;
	// data->player.y = 0;
	// data->player.angle = 0;
	// data->player.direction = 0;
	// data->player.dir_x = 0;
	// data->player.dir_y = 0;
	// data->player.plane_x = 0;
	// data->player.plane_y = 0;
}

static void init_textures(t_data *data) {
	data->texture->north = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	data->texture->east = NULL;
	data->texture->floor = NULL;
	data->texture->ceiling = NULL;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!error_check(ac, av))
		return (1);
	data = ft_malloc(sizeof(t_data));
	init_data(data);
	init_textures(data);
	init_player(data);
	parse_file(data, av[1]);
	init_001(data);
	return (0);
}
