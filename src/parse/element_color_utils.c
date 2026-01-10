/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:17:00 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/10 11:56:48 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

int	is_space_only(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*trim_spaces(char *s)
{
	int	len;

	while (*s && ft_isspace(*s))
		s++;
	len = ft_strlen(s);
	while (len > 0 && ft_isspace(s[len - 1]))
	{
		s[len - 1] = '\0';
		len--;
	}
	return (s);
}

char	*join_color_tokens(char **arr)
{
	char	*joined;
	char	*tmp;
	int		i;

	joined = ft_strdup("");
	i = 1;
	while (arr[i])
	{
		if (!is_space_only(arr[i]))
		{
			tmp = joined;
			joined = ft_strjoin(joined, arr[i]);
			(void)tmp;
		}
		i++;
	}
	return (joined);
}
