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

void	free_map(t_data *d)
{
	int	idx;

	if (!d->map)
		return ;
	idx = 0;
	while (d->map[idx])
	{
		ft_free(d->map[idx]);
		idx++;
	}
	ft_free(d->map);
	d->map = NULL;
}

static void	free_textures(t_data *d)
{
	if (d->tex_no)
		ft_free(d->tex_no);
	if (d->tex_so)
		ft_free(d->tex_so);
	if (d->tex_we)
		ft_free(d->tex_we);
	if (d->tex_ea)
		ft_free(d->tex_ea);
	d->tex_no = NULL;
	d->tex_so = NULL;
	d->tex_we = NULL;
	d->tex_ea = NULL;
}

void	free_data(t_data *d)
{
	free_textures(d);
	free_map(d);
}
