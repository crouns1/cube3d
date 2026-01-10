/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:16:57 by yabarhda          #+#    #+#             */
/*   Updated: 2025/08/28 18:33:28 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

char	*ft_strdup(const char *s)
{
	char		*d;
	size_t		i;
	size_t		src_len;

	i = 0;
	src_len = ft_strlen(s);
	d = ft_malloc(src_len + 1 * sizeof(char));
	while (i < (src_len + 1))
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
