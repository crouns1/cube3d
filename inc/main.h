/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:00:04 by yabarhda          #+#    #+#             */
/*   Updated: 2025/12/14 15:07:05 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <mlx.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_map	t_map;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}					t_mem;

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned char	*floor;
	unsigned char	*ceiling;
}					t_texture;

typedef struct s_map
{
	char			*row;
	int				size;
	t_map			*next;
}					t_map;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	char			direction;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_right;
	bool			key_left;
}					t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			*map;
	t_texture		*texture;
	t_player		player;
}					t_data;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
int		parse_file(t_data *data, char *file);
int		valid_map_char(char c);
int		ft_isdigit(int c);
int		ft_isplayer(char c);
int		on_keyrelease(int key, t_data *data);
int		on_keypress(int key, t_data *data);
int		clean_exit(t_data *data);

long	ft_atoi(const char *str);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);

void	*ft_malloc(long size);
void	ft_perror(char *s);
void	check_element(t_data *data, char **arr, int fd);
void	map_check(t_data *data, int fd);
void	validate_map(t_data *data);
void	move_player(t_data *data);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

#endif