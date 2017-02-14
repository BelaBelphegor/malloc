# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/02/14 21:52:18 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so
SRCS		=	malloc.c \
				free.c \
				show_alloc_memory.c \
				output.c \
				tools.c
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
	@ln -s $(NAME) libft_malloc.so
%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) -c $<

clean:
	rm -rf $(OBJS)

fclean:			clean
	rm -rf $(NAME)
	rm -rf libft_malloc.so

re: fclean all test

test: all
	gcc `pwd`/test/main.c -o `pwd`/test/test
	/usr/bin/time -l ./test/test
	env DYLD_LIBRARY_PATH=`pwd` DYLD_INSERT_LIBRARIES=libft_malloc.so DYLD_FORCE_FLAT_NAMESPACE=1 /usr/bin/time -l ./test/test

.PHONY: clean fclean re
