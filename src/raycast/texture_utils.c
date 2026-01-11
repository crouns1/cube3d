/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:00:00 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 02:29:32 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

t_img	*get_hit_texture(t_data *data)
{
	if (data->ray.side == 0 && data->ray.step_x < 0)
		return (&data->texture->west_tex);
	if (data->ray.side == 0)
		return (&data->texture->east_tex);
	if (data->ray.side == 1 && data->ray.step_y < 0)
		return (&data->texture->north_tex);
	return (&data->texture->south_tex);
}

int	get_texture_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len) + (x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

int	get_texture_x(t_data *data, t_img *tex, double distance)
{
	double	wall_x;
	int		tex_x;

	if (data->ray.side == 0)
		wall_x = data->ray.pos_y + distance * sin(data->ray.angle);
	else
		wall_x = data->ray.pos_x + distance * cos(data->ray.angle);
	wall_x -= floor(wall_x);
	tex_x = wall_x * tex->width;
	if ((data->ray.side == 0 && data->ray.step_x < 0) || \
		(data->ray.side == 1 && data->ray.step_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	set_draw_limits(double wall_h, double *start, double *end)
{
	*start = -wall_h / 2 + HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = wall_h / 2 + HEIGHT / 2;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}
