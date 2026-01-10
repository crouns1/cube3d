/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 12:06:10 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int	value_check(char *s, int fd)
{
	int	i;
	int	result;

	if (!s || s[0] == '\0' || s[0] == '\n')
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	i = 0;
	if (ft_strlen(s) > 4)
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '\n')
			(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
		i++;
	}
	result = ft_atoi(s);
	if (result < 0 || result > 255)
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	return (result);
}

static void	ensure_three_parts(char **parts, int fd)
{
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
}

static void	fill_colors(unsigned char *dst, char **parts, int fd)
{
	int		i;
	char	*tok;

	i = 0;
	while (i < 3)
	{
		tok = trim_spaces(parts[i]);
		if (tok[0] == '\0' || tok[0] == '\n')
			(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
		dst[i] = value_check(tok, fd);
		i++;
	}
}

void	assign_colors(char **arr, unsigned char **texture, int fd)
{
	char	**tmp_arr;
	char	*colors;

	if (*texture)
	{
		ft_malloc(-42);
		ft_perror("Multiple definitions of floor colors");
		close(fd);
		exit(1);
	}
	if (!arr[1])
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	colors = join_color_tokens(arr);
	colors = trim_spaces(colors);
	if (!valid_color_format(colors))
		(ft_malloc(-42), ft_perror("Invalid map"), close(fd), exit(1));
	tmp_arr = ft_split(colors, ',');
	ensure_three_parts(tmp_arr, fd);
	*texture = ft_malloc(sizeof(unsigned char) * 3);
	fill_colors(*texture, tmp_arr, fd);
}
