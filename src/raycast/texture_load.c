/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 15:54:36 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static t_img	load_texture(t_data *data, char *path)
{
	t_img	tex;

	tex.ptr = mlx_xpm_file_to_image(data->mlx, path, &tex.width, \
		&tex.height);
	if (!tex.ptr)
		(ft_perror("Invalid texture"), clean_exit(data));
	tex.addr = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.line_len, \
		&tex.endien);
	return (tex);
}

void	init_textures(t_data *data)
{
	data->texture->north_tex = load_texture(data, data->texture->north);
	data->texture->south_tex = load_texture(data, data->texture->south);
	data->texture->west_tex = load_texture(data, data->texture->west);
	data->texture->east_tex = load_texture(data, data->texture->east);
}
