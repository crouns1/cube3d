/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:00:04 by yabarhda          #+#    #+#             */
/*   Updated: 2026/01/11 15:40:38 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "/usr/include/minilibx-linux/mlx.h"
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
# define BLOCK 32
# define FOV 60
# define MOVE_SPEED 1

typedef struct s_map		t_map;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}					t_mem;

typedef struct s_ray
{
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	double			pos_x;
	double			pos_y;
	double			delta_x;
	double			delta_y;
	double			side_x;
	double			side_y;
	double			angle;
}					t_ray;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endien;
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
	t_img			north_tex;
	t_img			south_tex;
	t_img			west_tex;
	t_img			east_tex;
}					t_texture;

typedef struct s_map
{
	char			*row;
	int				size;
	t_map			*next;
}					t_map;

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
	char			direction;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_right;
	bool			key_left;
}					t_player;

typedef struct s_draw
{
	int				tex_x;
	int				y;
	double			distance;
	double			wall_h;
	double			start;
	double			end;
	double			step;
	double			tex_pos;
	t_img			*tex;
}					t_draw;

typedef struct s_data
{
	int				map_width;
	int				bpp;
	int				endien;
	int				size_line;
	int				width;
	int				height;
	int				map_height;
	char			*img_addr;
	char			**map_array;
	void			*mlx;
	void			*win;
	void			*img;
	t_map			*map;
	t_texture		*texture;
	t_player		player;
	t_ray			ray;
}					t_data;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
int		valid_map_char(char c);
int		ft_isdigit(int c);
int		ft_isplayer(char c);
int		on_gameupdate(t_data *data);
int		on_keypress(int key, t_data *data);
int		on_keyrelease(int key, t_data *data);
int		clean_exit(t_data *data);
int		is_wall(t_data *data, double x, double y);
int		only_spaces(char *line);
int		is_space_only(char *s);
int		valid_color_format(char *s);
int		get_texture_x(t_data *data, t_img *tex, double distance);
int		get_texture_color(t_img *tex, int x, int y);

long	ft_atoi(const char *str);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*trim_spaces(char *s);
char	*join_color_tokens(char **arr);

void	*ft_malloc(long size);
void	ft_perror(char *s);
void	check_element(t_data *data, char **arr, int fd);
void	map_check(t_data *data, int fd);
void	validate_map(t_data *data);
void	parse_file(t_data *data, char *file);
void	early_exit(char *error);
void	convert_map_to_array(t_data *data);
void	assign_texture(char **arr, char **texture, int fd);
void	assign_colors(char **arr, unsigned char **texture, int fd);
void	parse_elements(t_data *data, int fd);
void	require_elements(t_data *data, int fd);
void	check_texture_files(t_data *data, int fd);
void	add_node(t_map **map, t_map *new);
void	get_map_size(t_data *data);
void	standard_check(t_data *data);
void	deep_check(t_data *data);
void	check_borders(char **m);
void	move_player(t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);
void	init_cub(t_data *data);
void	draw_rays(t_data *data);
void	draw_floor_ceiling(t_data *data);
void	clear_window(t_data *data);
void	init_textures(t_data *data);
void	set_draw_limits(double wall_h, double *start, double *end);
void	fill_draw_data(t_data *data, t_draw *draw);

t_map	*new_node(char *row);

t_img	*get_hit_texture(t_data *data);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

#endif
