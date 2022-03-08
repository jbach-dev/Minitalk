# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbach <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 17:36:57 by jbach             #+#    #+#              #
#    Updated: 2022/02/07 18:20:02 by jbach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

UTILS = Libft/libft.c\
Libft/libft_2.c

OBJET_CLIENT = $(SRCS_CLIENT:.c=.o)

OBJET_SERVER = $(SRCS_SERVER:.c=.o)

BONUS_CLIENT = client_bonus.c
BONUS_SERVER = server_bonus.c

OBJET_CLIENT_BONUS = $(BONUS_CLIENT:.c=.o)

OBJET_SERVER_BONUS = $(BONUS_SERVER:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): client server

all: $(NAME)

client: $(OBJET_CLIENT)
	$(CC) $(OBJET_CLIENT) $(UTILS) -o $@

server: $(OBJET_SERVER)
	$(CC) $(OBJET_SERVER) $(UTILS) -o $@


bonus: client_bonus server_bonus

client_bonus: $(OBJET_CLIENT_BONUS)
	$(CC) $(OBJET_CLIENT_BONUS) $(UTILS) -o $@

server_bonus: $(OBJET_SERVER_BONUS)
	$(CC) $(OBJET_SERVER_BONUS) $(UTILS) -o $@

clean: 
	$(RM) $(OBJET_CLIENT) $(OBJET_SERVER) $(OBJET_CLIENT_BONUS) $(OBJET_SERVER_BONUS)

fclean: clean 
	$(RM) client server client_bonus server_bonus

re: fclean all
	
.PHONY: all clean fclean re
