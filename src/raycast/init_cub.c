/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:31:16 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 16:08:40 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	init_cub(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_malloc(-42);
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
	{
		ft_malloc(-42);
		exit(1);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_addr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line,
			&data->endien);
	mlx_hook(data->win, 17, 1L << 0, clean_exit, data);
	mlx_hook(data->win, 2, 1L << 0, on_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, on_keyrelease, data);
	mlx_loop_hook(data->mlx, on_gameupdate, data);
	mlx_loop(data->mlx);
}
