# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/02/16 18:12:19 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so
SRCS		=	malloc.c \
				memory_pool.c \
				realloc.c \
				free.c \
				show_alloc_memory.c \
				calloc.c \
				output.c \
				tools.c
INCLUDES	=	./includes
SRCSPATH	=	./srcs/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -fPIC
INCLUDES_O	=	-I $(INCLUDES)
SRC			=	$(addprefix $(SRCSPATH), $(SRCS))
OBJS		=	$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDE_C)
	@ln -s $(NAME) libft_malloc.so
%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJS)

fclean:			clean
	rm -rf $(NAME)
	rm -rf libft_malloc.so

re: fclean all

test: all
	make -C test/test_temoin
	make -C test/test_malloc
	make -C test/test_free
	make -C test/test_realloc
	make -C test/test_show
	make -C test/test_error

test_clean:
	make -C test/test_temoin fclean
	make -C test/test_malloc fclean
	make -C test/test_free fclean
	make -C test/test_realloc fclean
	make -C test/test_show fclean
	make -C test/test_error fclean

.PHONY: clean fclean re
