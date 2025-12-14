/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:25:59 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/14 09:49:50 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	cast_ray(t_data *data, t_ray *ray, int x)
{
	init_ray_direction(data, ray, x);
	init_ray_steps(data, ray);
	perform_dda(data, ray);
	calculate_wall_distance(data, ray);
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