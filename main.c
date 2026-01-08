/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 08:56:42 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 11:26:41 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "zero_protocol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (check_error(argc, argv))
		return (1);
	parse_bar_file(&data, argv[1]);
	free_data(&data);
	return (0);
}