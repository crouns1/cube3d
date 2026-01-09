/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:24:47 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/09 16:44:28 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

void	init_data(t_data *access)
{
	access->tex_no = NULL;
	access->tex_so = NULL;
	access->tex_we = NULL;
	access->tex_ea = NULL;
	access->floor[0] = -1;
	access->floor[1] = -1;
	access->floor[2] = -1;
	access->ceiling[0] = -1;
	access->ceiling[1] = -1;
	access->ceiling[2] = -1;
	access->map = NULL;
	access->map_width = 0;
	access->map_height = 0;
	access->player_x = -1;
	access->player_y = -1;
	access->player_dir = 0;
}