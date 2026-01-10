/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:18:58 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:56:29 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

void	check_element(t_data *data, char **arr, int fd)
{
	if (!ft_strcmp(arr[0], "NO"))
		assign_texture(arr, &data->texture->north, fd);
	else if (!ft_strcmp(arr[0], "SO"))
		assign_texture(arr, &data->texture->south, fd);
	else if (!ft_strcmp(arr[0], "WE"))
		assign_texture(arr, &data->texture->west, fd);
	else if (!ft_strcmp(arr[0], "EA"))
		assign_texture(arr, &data->texture->east, fd);
	else if (!ft_strcmp(arr[0], "F"))
		assign_colors(arr, &data->texture->floor, fd);
	else if (!ft_strcmp(arr[0], "C"))
		assign_colors(arr, &data->texture->ceiling, fd);
	else
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
}
