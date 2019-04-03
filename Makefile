NAME = ft_ssl
SRCS = $(addprefix srcs/, ft_ssl.c error.c struct.c flags.c parsing.c md5.c sha256.c func_nonlinear.c padding.c cut_blocks.c)
OBJ = $(SRCS:.c=.o)
LIBFT = libft/libft.a
LIBFT_PATH = libft/
INCLUDES = -I includes/ -I ./libft
CC = gcc
FLAGS = -Wall -Werror -Wextra -g -fsanitize=address

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ) && make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME) && make fclean -C $(LIBFT_PATH)

re: fclean all


