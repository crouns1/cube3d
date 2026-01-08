/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:04:42 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 11:02:39 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

size_t ft_strlen(char *str)
{
    int i =  0;
    while(str[i])
        i++;
    
    return i;
}

char    *err(char *str) {
    write(2, "Error\n", 6);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return str;
}

int check_error(int c , char **v) {
    int fd;
    int len;
    if(c != 2)
        {
            err("Not enough args");
            return 1;
        }
    fd = open(v[1] , O_RDONLY);
    if(fd == -1)
        return(err("No such file or dir\n") , 1);
    close(fd);
    len = strlen(v[1]);
    if(strcmp(".cub" , &v[1][len - 4]))
        return(err("Invalid file Format\n") , 1);
    return 0;
}