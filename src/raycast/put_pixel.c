/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:30:11 by yabarhda          #+#    #+#             */
/*   Updated: 2025/12/27 14:30:22 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int				index;
	unsigned char	*img;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	img = (unsigned char *)data->img_addr;
	index = (x * (data->bpp / 8)) + (y * data->size_line);
	img[index] = color & 0xFF;
	img[index + 1] = (color >> 8) & 0xFF;
	img[index + 2] = (color >> 16) & 0xFF;
	img[index + 3] = (color >> 24) & 0xFF;
}
