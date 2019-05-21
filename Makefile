##
## EPITECH PROJECT, 2019
## MyArpSpoof
## File description:
## Makefile
##

CC	=	gcc

SRC_DIR =	src

SRC	=	$(SRC_DIR)/main.c	\
		$(SRC_DIR)/parsing.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-g -Wall -Wextra -Iinclude

NAME	=	myARPspoof

RM	=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all re clean fclean
