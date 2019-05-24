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

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Iinclude -g

CFLAGSD	=	-g -Wall -Wextra -Iinclude

NAME	=	myARPspoof

RM	=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGSD) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all re clean fclean
