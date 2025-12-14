/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:59:43 by yabarhda          #+#    #+#             */
/*   Updated: 2025/12/14 10:15:24 by jait-chd         ###   ########.fr       */
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

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->map = NULL;
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
	data->player.key_w = false;
	data->player.key_a = false;
	data->player.key_s = false;
	data->player.key_d = false;
	data->player.key_right = false;
	data->player.key_left = false;
}

int	clean_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_malloc(-42);
	exit(0);
}

int	on_gameupdate(t_data *data)
{
	 move_player(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	init_cub(t_data *data)
{
	
	// then establish mlx and window
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	// create new image in memory to allow me manipulate pixels before displaying them
	// double buffering technic , also custom rendring
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// get the address of the image data to manipulate pixels directly
	// set pixels colors directly in memory
	data->img_addr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endien);
	// convert the full map into array so i can easily access it
	convert_map_to_array(data);
	mlx_hook(data->win, 17, 1L << 0, clean_exit, data);
	mlx_hook(data->win, 2, 1L << 0, on_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, on_keyrelease, data);
	mlx_loop_hook(data->mlx, on_gameupdate, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!error_check(ac, av))
		return (1);
	data = ft_malloc(sizeof(t_data));
	init_data(data);
	if (!parse_file(data, av[1]))
		return (ft_malloc(-42), 1);
		// this func is for init player pos and direction
	init_player(data);	
	init_cub(data);
	return (0);
}
