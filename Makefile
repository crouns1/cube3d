NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm

UTILS = $(addprefix src/utils/, ft_malloc.c ft_strcmp.c ft_strjoin.c ft_strdup.c \
		get_next_line.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_split.c ft_isspace.c \
		ft_strncmp.c ft_atoi.c ft_perror.c ft_strchr.c ft_isdigit.c ft_isplayer.c)

PARSE = $(addprefix src/parse/, check_element.c element_texture.c \
		element_color_utils.c element_color.c convert_map_to_array.c \
		early_exit.c parse_elements.c parse_texture_check.c map_nodes.c \
		map_check.c validate_size.c validate_player.c validate_borders.c \
		validate_deep.c parse_file.c validate_map.c utils.c valid_color_format.c )

RAYCAST = $(addprefix src/raycast/, game_loop.c init_cub.c player_movement.c put_pixel.c \
	raycast.c draw_secondaries.c texture_load.c texture_utils.c texture_draw.c)

HEADER = inc/main.h

SRC = src/main.c $(UTILS) $(PARSE) $(RAYCAST)

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
