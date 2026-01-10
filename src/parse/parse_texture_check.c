/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:57:23 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	check_one_texture(char *path, int f)
{
	char	buf[1];
	int		len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4))
		(ft_malloc(-42), ft_perror("Invalid texture file"), close(f), exit(1));
	fd = open(path, O_RDONLY);
	if (fd < 0 || read(fd, buf, 1) <= 0)
		(ft_malloc(-42), ft_perror("Invalid texture file"), close(f), exit(1));
	close(fd);
}

void	check_texture_files(t_data *data, int f)
{
	check_one_texture(data->texture->north, f);
	check_one_texture(data->texture->west, f);
	check_one_texture(data->texture->south, f);
	check_one_texture(data->texture->east, f);
}
