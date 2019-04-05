# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-goff <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 21:23:25 by ale-goff          #+#    #+#              #
#    Updated: 2018/10/09 12:54:42 by ale-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = basic_lists.c\
	  conversion.c\
	  flags_handle.c\
	  ft_printf.c\
	  helpers.c\
	  parse_args.c\
	  validate_fun.c\
	  wap.c\
	  helpers2.c\
	  helpers3.c\
	  principal_functions.c\
	  conversions2.c\
	  width_help.c\
	  helpers5.c\
	  helpers4.c

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): 
	gcc -c $(FLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
