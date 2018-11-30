# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qpeng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 23:44:47 by qpeng             #+#    #+#              #
#    Updated: 2018/09/20 01:01:02 by qpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = b_ls

FLAGS =  -Wall -Werror -Wextra 

CFLAGS = -c -Wall -Werror -Wextra 

SRCSDIR = srcs

CFILES = ft_*.c

HEADER = -I./includes

SRCS = $(addprefix $(SRCSDIR)/, $(CFILES))

OBJS = $(SRCS:.c=.o)

OBJSDIR = objects

all: $(NAME) 

$(NAME): $(OBJS)
	ar rc $(NAME) ./$(OBJSDIR)/*.o
	ranlib $(NAME)

$(OBJS): 
	mkdir $(OBJSDIR)
	gcc $(CFLAGS) $(HEADER) $(SRCS)
	mv *.o $(OBJSDIR)

clean:
	/bin/rm -rf $(OBJSDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
