/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_protocol.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 08:58:28 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 11:35:10 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZERO_PROTOCOL_H
# define ZERO_PROTOCOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>


typedef struct s_data
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor[3];
	int		ceiling[3];
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_data;

int		check_error(int c, char **v);
char	*err(char *str);
void	init_data(t_data *d);
void	parse_bar_file(t_data *data, char *file);
char	*read_file_content(const char *path);
char	**split_lines(char *content);
void	free_lines(char **lines);
char	*skip_spaces(char *s);
int		parse_header_line(t_data *d, char *line);
int		parse_color(int out[3], char *line);
int		set_texture(char **dst, char *line);
int		is_map_line(char *line);
int		build_map(t_data *d, char **lines, int start);
int		validate_map(t_data *d);
void	free_map(t_data *d);
void	free_data(t_data *d);
void	*ft_malloc(int size);
void	ft_free(void *ptr);

#endif