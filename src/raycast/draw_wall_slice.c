/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:26:16 by jait-chd          #+#    #+#             */
/*   Updated: 2025/12/14 09:54:03 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	draw_wall_slice(t_data *data, t_ray *ray, int x, int line_height)
{
    (void)ray;
    int	draw_start;
    int	draw_end;

    draw_start = -line_height / 2 + HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT)
        draw_end = HEIGHT - 1;
    draw_vertical_line(data, x, draw_start, draw_end, 0x0FFFFF);
    draw_vertical_line(data, x, 0, draw_start, 0x0263238);
    draw_vertical_line(data, x, draw_end, HEIGHT, 0x0263238);
}