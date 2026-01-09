/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:10:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 11:10:00 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

void	free_map(t_data *data)
{
	int	idx;

	if (!data->map)
		return ;
	idx = 0;
	while (data->map[idx])
	{
		ft_free(data->map[idx]);
		idx++;
	}
	ft_free(data->map);
	data->map = NULL;
}

static void	free_textures(t_data *data)
{
	if (data->tex_no)
		ft_free(data->tex_no);
	if (data->tex_so)
		ft_free(data->tex_so);
	if (data->tex_we)
		ft_free(data->tex_we);
	if (data->tex_ea)
		ft_free(data->tex_ea);
	data->tex_no = NULL;
	data->tex_so = NULL;
	data->tex_we = NULL;
	data->tex_ea = NULL;
}

void	free_data(t_data *d)
{
	free_textures(d);
	free_map(d);
}
