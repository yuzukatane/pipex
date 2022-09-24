NAME = pipex
CFLAGS = -Wall -Wextra -Werror
CC = gcc
SRCS = main.c utils_init.c utils_check.c utils_free.c pipex.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

visu: $(NAME)
	cp $(NAME) push_swap_visualizer/$(NAME)
	./push_swap_visualizer/build/bin/visualizer

.PHONY: all clean fclean re
