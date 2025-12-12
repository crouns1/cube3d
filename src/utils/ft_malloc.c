/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:14:06 by yabarhda          #+#    #+#             */
/*   Updated: 2025/08/31 19:00:21 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

static void	free_all(t_mem *mem)
{
	t_mem	*tmp;

	while (mem)
	{
		free(mem->ptr);
		tmp = mem;
		mem = mem->next;
		free(tmp);
	}
}

static void	ft_malloc_failsafe(t_mem *mem)
{
	free_all(mem);
	write(2, "minishell: malloc somehow failed\n", 33);
	exit(1);
}

void	*ft_malloc(long size)
{
	static t_mem *(head), *(tail);
	t_mem *(new);
	void *(ptr);
	if (size == -42)
		return (free_all(head), NULL);
	ptr = malloc(size);
	if (!ptr)
		ft_malloc_failsafe(head);
	new = malloc(sizeof(t_mem));
	if (!new)
		(free(ptr), ft_malloc_failsafe(head));
	new->ptr = ptr;
	new->next = NULL;
	if (!head)
	{
		head = new;
		tail = new;
	}
	else
	{
		tail->next = new;
		tail = new;
	}
	return (ptr);
}
