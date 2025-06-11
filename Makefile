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

SRC_DIR = server_bonus.c client_bonus.c safe_atoi.c
INLCUDE = minitalk.h

SRC_1 = server_bonus.c
SRC_2 = client_bonus.c safe_atoi.c
OBJ_1 := $(SRC_1:.c=.o)
OBJ_2 := $(SRC_2:.c=.o)

all : $(NAME_1) $(NAME_2)

$(NAME_1): $(OBJ_1)
		$(CC) $(CFLAGS) -o $@ $<

$(NAME_2): $(OBJ_2)
		$(CC) $(CFLAGS) -o $@ $(OBJ_2)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJ_1) $(OBJ_2)

fclean: clean
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

.PHONY: all clean fclean re
