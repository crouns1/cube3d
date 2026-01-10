/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 12:08:44 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int	only_newline_or_empty(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	assign_texture(char **arr, char **texture, int fd)
{
	if (*texture)
	{
		ft_malloc(-42);
		ft_perror("Multiple definitions of textures");
		close(fd);
		exit(1);
	}
	if (!arr[1] || (arr[2] && !only_newline_or_empty(arr[2])))
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	if (arr[1][ft_strlen(arr[1]) - 1] == '\n')
	{
		*texture = ft_malloc(sizeof(char) * ft_strlen(arr[1]));
		ft_strlcpy(*texture, arr[1], ft_strlen(arr[1]));
	}
	else
		*texture = arr[1];
}
