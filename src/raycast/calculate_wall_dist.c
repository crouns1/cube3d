/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_dist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:26:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/14 10:21:47 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	calculate_wall_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ((double)ray->map_x - data->player.x + (1.0 - (double)ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = ((double)ray->map_y - data->player.y + (1.0 - (double)ray->step_y) / 2.0) / ray->dir_y;
}