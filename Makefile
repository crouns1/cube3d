NAME = cub3D
CC = clang#cc
CFLAGS = -Wall -Wextra -Werror -g
MLX = -lmlx -lXext -lX11 -lm

UTILS = $(addprefix src/utils/, ft_malloc.c ft_strcmp.c ft_strjoin.c ft_strdup.c \
		get_next_line.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_split.c ft_isspace.c \
		ft_strncmp.c ft_atoi.c ft_perror.c ft_strchr.c ft_isdigit.c ft_isplayer.c)

PARSE = $(addprefix src/parse/, check_element.c map_check.c parse_file.c \
		validate_map.c)

RAYCAST = $(addprefix src/raycast/, switch_to_array.c raycast_drawing.c raycast_ray.c \
		raycast_movement.c raycast_init.c perform_dda.c load_textures.c)

SRC = src/main.c $(UTILS) $(PARSE) $(RAYCAST)

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
