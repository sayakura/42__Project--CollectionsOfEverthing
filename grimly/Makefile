# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qpeng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 18:52:52 by qpeng             #+#    #+#              #
#    Updated: 2018/12/02 18:54:30 by qpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = grimly

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Werror -Wextra libft/*.c -I libft/libft.h
	@ar -q libft/libft.a *.o
	@gcc -Llibft -lft *.c -o grimly

clean:
	@rm -rf *.o *.a libft/*.a libft/*.o

fclean: clean
	@rm -rf grimly

re: fclean all
