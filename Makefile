# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2016/07/21 07:14:08 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so
SRCS		=	malloc.c
INCLUDES	=	./includes
SRCSPATH	=	./srcs/
CC			=	gcc
CFLAFGS		=	-Wall -Werror -Wextra
INCLUDES_O	=	-I $(INCLUDES)
SRC			=	$(addprefix $(SRCSPATH), $(SRCS))
OBJS		=	$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDE_C)
	@ln -s libft_malloc.so
%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) -c $<

clean:
	rm -rf $(OBJS)

fclean:			clean
	rm -rf $(NAME)
	rm -rf libft_malloc.so

re: fclean all

.PHONY: clean fclean re
