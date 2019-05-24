##
## EPITECH PROJECT, 2019
## MyArpSpoof
## File description:
## Makefile
##

CC	=	gcc

SRC_DIR =	src

SRC	=	$(SRC_DIR)/main.c		\
		$(SRC_DIR)/parsing.c		\
		$(SRC_DIR)/socket.c		\
		$(SRC_DIR)/get_mac_addr.c	\
		$(SRC_DIR)/get_mac_addr_2.c 	\
		$(SRC_DIR)/receive_arp.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Iinclude -g

NAME	=	myARPspoof

RM	=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all re clean fclean
