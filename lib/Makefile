##
## EPITECH PROJECT, 2021
## myrunner
## File description:
## Makefile
##

SRC	=	my_get_nbr.c	\
		my_put_nbr.c	\
		my_putchar.c	\
		my_putstr.c		\
		my_strlen.c		\

OBJ	=	$(SRC:.c=.o)

NAME	=	lib.a

$(NAME):	$(OBJ)
	ar	rc	$(NAME)	$(OBJ)

clean:
	rm	-f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean	all
