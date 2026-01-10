/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_color_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 12:06:43 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static int	is_valid_color_char(char c, char prev, int *commas)
{
	if (c == ',')
	{
		if (prev == ',' || prev == 0)
			return (0);
		(*commas)++;
	}
	else if (!ft_isdigit(c))
		return (0);
	return (1);
}

int	valid_color_format(char *s)
{
	char	prev;
	int		commas;
	int		i;

	if (!s)
		return (0);
	prev = 0;
	commas = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			i++;
			continue ;
		}
		if (!is_valid_color_char(s[i], prev, &commas))
			return (0);
		prev = s[i];
		i++;
	}
	return (prev && prev != ',' && commas == 2);
}
