# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/03/10 16:03:18 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		fractol

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror

INCLUDE 	=		-I include -I libft/include

LIB 		=		libft/libft.a -L /usr/local/lib/ -lmlx\
					-framework OpenGL \
					-framework AppKit -lm

SRCS		=		src/camera.c		\
					src/color.c			\
					src/equation.c		\
					src/fdf.c			\
					src/image.c			\
					src/input.c			\
					src/mlx_data.c		\
					src/parseur.c		\
					src/rmesh.c			\
					src/vector2.c		\
					src/vector3.c		\
					src/vector3_calc.c	\


OBJS		=		$(SRCS:.c=.o)

all			: 		$(NAME)

%.o			:		%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(NAME)		:		libft/include/libft.h include/fdf.h $(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB) -o $(NAME) $(OBJS)
	@echo "Compilation" $(NAME) "Terminee"

clean 		:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean		:		clean
	@make fclean -C libft
	@rm -rf $(NAME)

start		:		all
	$(shell ./$(NAME) mandelbrot)

re			:		fclean all

.PHONY: all clean flcean re start