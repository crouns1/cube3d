/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:21:01 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/15 07:33:49 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	load_single_texture(t_data *data, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, 
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_malloc(-42);
		ft_perror("Failed to load texture");
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(int *)pixel);
}

void	load_textures(t_data *data)
{
	load_single_texture(data, &data->texture->north_img, data->texture->north);
	load_single_texture(data, &data->texture->south_img, data->texture->south);
	load_single_texture(data, &data->texture->west_img, data->texture->west);
	load_single_texture(data, &data->texture->east_img, data->texture->east);
}
