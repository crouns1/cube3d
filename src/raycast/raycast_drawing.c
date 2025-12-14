/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:25:59 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/14 18:40:18 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/main.h"

static int	rgb_to_color(unsigned char *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static t_img	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (&data->texture->east_img);
	else if (ray->side == 0 && ray->step_x < 0)
		return (&data->texture->west_img);
	else if (ray->side == 1 && ray->step_y > 0)
		return (&data->texture->south_img);
	else
		return (&data->texture->north_img);
}

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

static void	draw_wall_slice(t_data *data, t_ray *ray, int x, int line_height)
{
	int		draw_start;
	int		draw_end;
	int		ceiling_color;
	int		floor_color;
	t_img	*texture;
	int		tex_x;
	int		y;
	int		tex_y;
	float	step;
	float	tex_pos;
	int		color;

	texture = get_wall_texture(data, ray);
	tex_x = (int)(ray->wall_x * texture->width);
	if ((ray->side == 0 && ray->step_x < 0) 
		|| (ray->side == 1 && ray->step_y > 0))
		tex_x = texture->width - tex_x - 1;
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	ceiling_color = rgb_to_color(data->texture->ceiling);
	floor_color = rgb_to_color(data->texture->floor);
	step = 1.0 * texture->height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	draw_vertical_line(data, x, 0, draw_start, ceiling_color);
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_texture_pixel(texture, tex_x, tex_y);
		put_pixel(data, x, y, color);
		y++;
	}
	draw_vertical_line(data, x, draw_end, HEIGHT, floor_color);
}

void	raycast(t_data *data)
{
	t_ray	ray;
	int		x;
	int		line_height;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(data, &ray, x);
		line_height = (int)(HEIGHT / ray.perp_wall_dist);
		draw_wall_slice(data, &ray, x, line_height);
		x++;
	}
}
