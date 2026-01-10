/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:57:47 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	set_player(t_data *data, int x, int y, char *cell)
{
	if (data->player.x)
		(ft_malloc(-42), ft_perror("Invalid map"), exit(1));
	data->player.x = (x + 0.5) * BLOCK;
	data->player.y = (y + 0.5) * BLOCK;
	data->player.direction = *cell;
	*cell = '0';
}

static void	scan_row(t_data *data, char *row, int y)
{
	int	x;

	x = 0;
	while (row[x])
	{
		if (ft_isplayer(row[x]))
			set_player(data, x, y, &row[x]);
		x++;
	}
}

void	standard_check(t_data *data)
{
	int		y;
	t_map	*tmp;

	y = 0;
	tmp = data->map;
	while (tmp)
	{
		scan_row(data, tmp->row, y);
		y++;
		tmp = tmp->next;
	}
	if (!data->player.x)
		(ft_malloc(-42), ft_perror("Player not found"), exit(1));
}
