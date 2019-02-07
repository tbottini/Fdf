# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by yberramd          #+#    #+#              #
#    Updated: 2019/02/07 21:35:46 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I /usr/local/include

LIB = libft/libft.a -L /usr/local/lib/ -lmlx -framework OpenGL \
		-framework AppKit -lm

SRCS = 	fdf.c 		\
		equation.c 	\
		parseur.c	\
		vector2.c	\
		vector3.c	\
		image.c		\
		rmesh.c 	\
		input.c 	\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS) fdf.h
	make -C libft/
	$(CC) -o $(NAME) $(CFLAGS) $(SRCS) $(LIB)

clean :
	make clean -C libft/
	rm -rf $(OBJS)

fclean : clean
	make fclean -C libft/
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean flcean re
