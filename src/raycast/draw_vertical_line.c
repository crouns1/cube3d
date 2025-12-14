/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:26:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/14 09:54:50 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void check_x_y(int x, int y) {
	if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	check_x_y(x , y);
	dst = data->img_addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		put_pixel(data, x, y, color);
		y++;
	}
}