CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I/opt/X11/include -Imlx
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

NAME = so_long

SRCS = 	bonus/main.c				\
		bonus/input.c				\
		bonus/render.c				\
		bonus/map.c					\
		bonus/map_aux.c				\
		bonus/map_check.c			\
		bonus/get_next_line.c		\
		bonus/get_next_line_utils.c \
		bonus/itoa.c				\
		bonus/enemy.c				\
		bonus/initialize.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

bonus: $(NAME)

.PHONY: clean fclean re
