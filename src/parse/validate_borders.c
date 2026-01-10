/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:57:26 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	check_neighbors(char **m, int i, int j)
{
	if (!m[i][j + 1] || (m[i][j + 1] != '0' && m[i][j + 1] != '1'))
		early_exit("Invalid map");
	if (j == 0 || !m[i][j - 1] || (m[i][j - 1] != '0' && m[i][j - 1] != '1'))
		early_exit("Invalid map");
	if (!m[i + 1] || j >= (int)ft_strlen(m[i + 1]) || !m[i + 1][j]
		|| (m[i + 1][j] != '0' && m[i + 1][j] != '1'))
		early_exit("Invalid map");
	if (i == 0 || j >= (int)ft_strlen(m[i - 1]) || !m[i - 1][j]
		|| (m[i - 1][j] != '0' && m[i - 1][j] != '1'))
		early_exit("Invalid map");
}

static void	check_row(char **m, int i)
{
	int	j;

	j = 0;
	while (m[i][j])
	{
		if (m[i][j] == '0')
			check_neighbors(m, i, j);
		j++;
	}
}

void	check_borders(char **m)
{
	int	i;

	i = 0;
	while (m[i])
	{
		check_row(m, i);
		i++;
	}
}
