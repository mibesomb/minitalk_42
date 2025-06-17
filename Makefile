# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 21:21:22 by mibesomb          #+#    #+#              #
#    Updated: 2025/06/10 21:21:25 by mibesomb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = server
NAME_2 = client

CC = cc
CFLAGS = -Wextra -Werror -Wall


SRC_1 = server.c utils_server.c ft_itoa.c ft_strlen.c
SRC_2 = client.c utils_client.c ft_atoi.c ft_strlen.c
CFLAGS = -Wextra -Werror -Wall

OBJ_1 := $(SRC_1:.c=.o)
OBJ_2 := $(SRC_2:.c=.o)

all : $(NAME_1) $(NAME_2)

$(NAME_1): $(OBJ_1)
		$(CC) $(CFLAGS) -o $@ $(OBJ_1)

$(NAME_2): $(OBJ_2)
		$(CC) $(CFLAGS) -o $@ $(OBJ_2)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJ_1) $(OBJ_2)

fclean: clean
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

.PHONY: all clean fclean re