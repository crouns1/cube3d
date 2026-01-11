/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:49:45 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/10 13:32:08 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2 || !n)
		return (0);
	while (s1[i] || s2[i])
	{
		if (i < n)
		{
			if (s1[i] != s2[i])
				break ;
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
