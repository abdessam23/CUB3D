NAME = cube

CC = cc
FLAGS = -Wall -Wextra -Werror  

SRC =  raycast/draw_tex.c raycast/handle_keys.c raycast/init_game.c raycast/run_game.c parsing/pars_map.c  main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx  minilibx-linux/libmlx_Linux.a libft/libft.a -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
