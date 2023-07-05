# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 08:19:48 by crigonza          #+#    #+#              #
#    Updated: 2023/07/05 21:05:53 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc -g -fsanitize=thread
CFLAGS	= -Wall -Werror -Wextra 

SRCS 	= 	./src/main.c \
			./src/philos.c \
			./src/states.c \
			./src/utils.c \
			./src/check_args.c \
			
OBJS	= ${SRCS:%.c=%.o}

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean:clean
	@rm -f $(NAME)

re:	clean all

.PHONY: all, clean, fclean, re