NAME		:= cub3d
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
INCLUDES	:= -I. -Iget_next_line
RM		:= rm -f

SRCS		:= \
	main.c \
	check_error.c \
	init_data.c \
	parse_.bar.c \
	parse_header.c \
	parse_map.c \
	parse_read.c \
	free_data.c \
	mem_utils.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

OBJS		:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
