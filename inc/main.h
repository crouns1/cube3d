/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:00:04 by yabarhda          #+#    #+#             */
/*   Updated: 2025/12/14 18:40:18 by yabarhda         ###   ########.fr       */
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
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define PI 3.14159265359

typedef struct s_map t_map;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}					t_mem;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned char	*floor;
	unsigned char	*ceiling;
	t_img			north_img;
	t_img			south_img;
	t_img			west_img;
	t_img			east_img;
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
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_right;
	bool			key_left;
}					t_player;

typedef struct s_ray
{
	float			dir_x;
	float			dir_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			perp_wall_dist;
	float			wall_x;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				map_x;
	int				map_y;
}					t_ray;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void 			*img;
	char			*img_addr;
	int 			bpp;
	int 			size_line;
	int 			endien;
	int 			width;
	int 			height;
	t_map			*map;
	t_texture		*texture;
	t_player		player;
	char			**map_array;
	int				map_width;
	int				map_height;
}					t_data;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
int		valid_map_char(char c);
int		ft_isdigit(int c);
int		ft_isplayer(char c);

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
void	init_player_direction(t_data *data);
void	convert_map_to_array(t_data *data);
void	raycast(t_data *data);
void	cast_ray(t_data *data, t_ray *ray, int x);
void	draw_vertical_line(t_data *data, int x, int start, int end, int color);
void	put_pixel(t_data *data, int x, int y, int color);
void	perform_dda(t_data *data, t_ray *ray);
void	handle_movement(t_data *data);
void	rotate_player(t_data *data, float angle);
void	load_textures(t_data *data);
int		get_texture_pixel(t_img *texture, int x, int y);
void	parse_file(t_data *data, char *file);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

#endif