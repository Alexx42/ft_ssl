NAME = ft_ssl
SRCS = $(addprefix srcs/, ft_ssl.c error.c struct.c flags.c parsing.c md5.c sha256.c print.c struct2.c)
OBJ = $(SRCS:.c=.o)
LIBFT = libft/libft.a
LIBFT_PATH = libft/
PRINTF = ft_printf/libftprintf.a
PRINTF_PATH = ft_printf/
INCLUDES = -I includes/ -I ./libft
CC = gcc
FLAGS = -Wall -Werror -Wextra
all: $(NAME)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	make -C $(PRINTF_PATH)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

clean:
	rm -f $(OBJ) && make clean -C $(LIBFT_PATH) && make clean -C $(PRINTF_PATH)

fclean: clean
	rm -f $(NAME) && make fclean -C $(LIBFT_PATH) && make fclean -C $(PRINTF_PATH)

re: fclean all
