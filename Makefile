# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 08:19:48 by crigonza          #+#    #+#              #
#    Updated: 2023/06/29 08:15:25 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

HEADERS = -I ./inc
SRCS 	= 	./src/main.c \
			./src/philos.c \
			./src/states.c \
			./src/utils.c \
			./src/check_args.c \
			
OBJS	= ${SRCS:.c=.o}

%.o: &.c
	@$(CC) $(CFLAGS)  -o $@ -c $< $(HEADERS)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean:clean
	@rm -f $(NAME)

re:	clean all

.PHONY: all, clean, fclean, re