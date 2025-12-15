/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:26:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/15 07:34:27 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	init_ray_direction(t_data *data, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray->dir_y = data->player.dir_y + data->player.plane_y * camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

static void	init_ray_steps(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y) * ray->delta_dist_y;
	}
}


static void	calculate_wall_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.x 
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.y 
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->side == 0)
		ray->wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	cast_ray(t_data *data, t_ray *ray, int x)
{
	init_ray_direction(data, ray, x);
	init_ray_steps(data, ray);
	perform_dda(data, ray);
	calculate_wall_distance(data, ray);
}
